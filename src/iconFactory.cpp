// TODO implementation
#include "iconFactory.h"

IconFactory& IconFactory::instance() {
    static IconFactory inst;
    return inst;
}

Icon IconFactory::create(IconType type, IconParams& params) const {
    switch (type) {
        case IconType::Block: 
            return Icon(params.size.height(), vector<Cell>(params.size.width(), Cell{params.color, params.ascii}));
        default:
            return Icon{};
    }
}