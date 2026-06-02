#include "Shared.h"
#include <vector>

class ElementArray
{
    public:
        unsigned int ebo;
        ElementArray(std::vector<unsigned int>& indices);
        void bind();
        void unbind();
};
