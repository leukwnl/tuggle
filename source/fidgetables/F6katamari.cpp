//
//  F6katamari.cpp
//  Tuggle
//
//  Implementation of F6katamari - a single button toy.
//

#include "F6katamari.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Teal/Cyan color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(0, 206, 209, 255)    // Dark turquoise
#define BUTTON_COLOR_PRESSED    Color4(0, 176, 179, 255)    // Darker teal
#define BUTTON_COLOR_INACTIVE   Color4(130, 225, 230, 255)  // Dimmed teal

#pragma mark -
#pragma mark Constructors

F6katamari::F6katamari() : FidgetableView(), _buttonRadius(100.0f) {}

F6katamari::~F6katamari() {
    dispose();
}

bool F6katamari::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F6katamari> F6katamari::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F6katamari> result = std::make_shared<F6katamari>();
    if (result->init(6, pageSize)) {
        return result;
    }
    return nullptr;
}

void F6katamari::dispose() {
    if (_button != nullptr) {
        _button->deactivate();
        _button->clearListeners();
        _button = nullptr;
    }
    _buttonNode = nullptr;
    FidgetableView::dispose();
}

#pragma mark -
#pragma mark Content Building

void F6katamari::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f6katamari_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F6katamari::onPressed() {
    CULog("F6katamari pressed");
}

void F6katamari::update(float timestep) {
    FidgetableView::update(timestep);
}

void F6katamari::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F6katamari::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F6katamari::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

