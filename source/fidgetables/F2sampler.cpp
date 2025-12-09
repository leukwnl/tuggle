//
//  F2sampler.cpp
//  Tuggle
//
//  Implementation of F2sampler - a single button toy.
//

#include "F2sampler.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Coral/Salmon color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(250, 128, 114, 255)  // Salmon
#define BUTTON_COLOR_PRESSED    Color4(220, 98, 84, 255)    // Darker salmon
#define BUTTON_COLOR_INACTIVE   Color4(255, 180, 170, 255)  // Dimmed salmon

#pragma mark -
#pragma mark Constructors

F2sampler::F2sampler() : FidgetableView(), _buttonRadius(100.0f) {}

F2sampler::~F2sampler() {
    dispose();
}

bool F2sampler::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F2sampler> F2sampler::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F2sampler> result = std::make_shared<F2sampler>();
    if (result->init(2, pageSize)) {
        return result;
    }
    return nullptr;
}

void F2sampler::dispose() {
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

void F2sampler::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f2sampler_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F2sampler::onPressed() {
    CULog("F2sampler pressed");
}

void F2sampler::update(float timestep) {
    FidgetableView::update(timestep);
}

void F2sampler::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F2sampler::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F2sampler::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

