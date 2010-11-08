#pragma once

#include "Foundation/Automation/Event.h"

#include "Foundation/Document/Document.h"

#include "Pipeline/API.h"
#include "Pipeline/Asset/Classes/SceneAsset.h"
#include "Pipeline/SceneGraph/Selection.h"
#include "Pipeline/SceneGraph/Scene.h"
#include "Pipeline/SceneGraph/Pick.h"
#include "Pipeline/SceneGraph/Render.h"

namespace Helium
{
    namespace Asset
    {
        class SceneAsset;
        typedef Helium::SmartPtr< SceneAsset > SceneAssetPtr;
    }

    namespace SceneGraph
    {
        // Forwards
        class HierarchyNode;
        class Viewport;

        struct FilePathChangedArgs;
        struct NodeChangeArgs;

        struct SceneChangeArgs
        {
            SceneGraph::Scene* m_Scene;

            SceneChangeArgs (SceneGraph::Scene* scene)
                : m_Scene (scene)
            {
            }
        };

        typedef Helium::Signature< const SceneChangeArgs& > SceneChangeSignature;


        /////////////////////////////////////////////////////////////////////////////
        // Tracks all the scenes and their undo queues.
        // 
        class PIPELINE_API SceneManager
        {
        private:
            // all loaded scenes by path
            M_SceneSmartPtr m_Scenes;

            // scenes by document
            typedef std::map< const Document*, SceneGraph::Scene* > M_DocumentToSceneTable;
            M_DocumentToSceneTable m_DocumentToSceneTable;

            typedef std::map< SceneGraph::Scene*, const Document* > M_SceneToDocumentTable;
            M_SceneToDocumentTable m_SceneToDocumentTable;

            // the nested scenes that can be freed
            M_AllocScene m_AllocatedScenes;

            // the current scene
            SceneGraph::Scene* m_CurrentScene;

        public:
            SceneManager();
            ~SceneManager();

            ScenePtr NewScene( SceneGraph::Viewport* viewport, const Document* document, bool nested = false );
            ScenePtr OpenScene( SceneGraph::Viewport* viewport, const Document* document, tstring& error );

            void AddScene( SceneGraph::Scene* scene );
            SceneGraph::Scene* GetScene( const Document* document ) const;
            SceneGraph::Scene* GetScene( const tstring& path ) const;
            const M_SceneSmartPtr& GetScenes() const;
            void RemoveScene( SceneGraph::Scene* scene );
            void RemoveAllScenes();

            bool IsNestedScene( SceneGraph::Scene* scene ) const;
            void ReleaseNestedScene( SceneGraph::Scene*& scene );

            static tstring GetUniqueFileName();

            bool HasCurrentScene() const;
            bool IsCurrentScene( const SceneGraph::Scene* sceneToCompare ) const;

            SceneGraph::Scene* GetCurrentScene() const;
            void SetCurrentScene( SceneGraph::Scene* scene );

            // Undo/redo support
            bool CanUndo();
            bool CanRedo();
            void Undo();
            void Redo();
            void Push( Undo::Queue* queue );

        private:
            SceneGraph::Scene* FindFirstNonNestedScene() const;
            void OnSceneEditing( const SceneEditingArgs& args );
            
            void DocumentSave( const DocumentEventArgs& args );
            void DocumentClosed( const DocumentEventArgs& args );
            void DocumentPathChanged( const DocumentPathChangedArgs& args );

        public:
            SceneChangeSignature::Event e_SceneAdded;
            SceneChangeSignature::Event e_SceneRemoving;
            SceneChangeSignature::Event e_CurrentSceneChanging;
            SceneChangeSignature::Event e_CurrentSceneChanged;
        };
    }
}
