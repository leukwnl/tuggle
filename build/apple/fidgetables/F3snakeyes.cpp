//
//  F3snakeyes.cpp
//  Tuggle
//
//  Implementation of F3snakeyes - a single button toy.
//

#include "F3snakeyes.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Mint/Sea Green color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(60, 179, 113, 255)   // Medium sea green
#define BUTTON_COLOR_PRESSED    Color4(40, 149, 83, 255)    // Darker green
#define BUTTON_COLOR_INACTIVE   Color4(140, 210, 170, 255)  // Dimmed green

#pragma mark -
#pragma mark Constructors

F3snakeyes::F3snakeyes() : FidgetableView(), _buttonRadius(100.0f) {}

F3snakeyes::~F3snakeyes() {
    dispose();
}

bool F3snakeyes::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F3snakeyes> F3snakeyes::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F3snakeyes> result = std::make_shared<F3snakeyes>();
    if (result->init(3, pageSize)) {
        return result;
    }
    return nullptr;
}

void F3snakeyes::dispose() {
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

void F3snakeyes::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f3snakeyes_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F3snakeyes::onPressed() {
    CULog("F3snakeyes pressed");
}

void F3snakeyes::update(float timestep) {
    FidgetableView::update(timestep);
}

void F3snakeyes::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F3snakeyes::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F3snakeyes::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

