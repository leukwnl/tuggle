//
//  F7samba.cpp
//  Tuggle
//
//  Implementation of F7samba - a single button toy.
//

#include "F7samba.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Hot Pink/Magenta color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(255, 105, 180, 255)  // Hot pink
#define BUTTON_COLOR_PRESSED    Color4(225, 75, 150, 255)   // Darker pink
#define BUTTON_COLOR_INACTIVE   Color4(255, 175, 210, 255)  // Dimmed pink

#pragma mark -
#pragma mark Constructors

F7samba::F7samba() : FidgetableView(), _buttonRadius(100.0f) {}

F7samba::~F7samba() {
    dispose();
}

bool F7samba::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F7samba> F7samba::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F7samba> result = std::make_shared<F7samba>();
    if (result->init(7, pageSize)) {
        return result;
    }
    return nullptr;
}

void F7samba::dispose() {
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

void F7samba::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f7samba_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F7samba::onPressed() {
    CULog("F7samba pressed");
}

void F7samba::update(float timestep) {
    FidgetableView::update(timestep);
}

void F7samba::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F7samba::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F7samba::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

