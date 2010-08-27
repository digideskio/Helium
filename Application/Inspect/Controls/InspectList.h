#pragma once

#include "Application/API.h"
#include "Application/Inspect/Controls/InspectControl.h"

namespace Helium
{
    namespace Inspect
    {
        const static tchar LIST_ATTR_SORTED[]    = TXT( "sorted" );

        namespace MoveDirections
        {
            enum MoveDirection
            {
                Up,
                Down
            };
        }
        typedef MoveDirections::MoveDirection MoveDirection;

        struct AddItemArgs
        {
            AddItemArgs()
            {
            }
        };
        typedef Helium::Signature< void, const AddItemArgs& > AddItemSignature;

        class APPLICATION_API List : public Reflect::ConcreteInheritor<List, Control>
        {
        public:
            List();

            virtual bool Process(const tstring& key, const tstring& value) HELIUM_OVERRIDE;

            AddItemSignature::Event             e_AddItem;
            Attribute< bool >                   a_IsSorted;
            Attribute< std::set< size_t > >     a_SelectedItemIndices;
        };

        typedef Helium::SmartPtr<List> ListPtr;
    }
}
