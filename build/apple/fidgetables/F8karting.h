//
//  F8karting.h
//  Tuggle
//
//  Eighth fidgetable toy - a single interactive button.
//

#ifndef __F8KARTING_H__
#define __F8KARTING_H__

#include "FidgetableView.h"

/**
 * Eighth fidgetable toy in the carousel.
 * Currently displays a single circular button.
 */
class F8karting : public FidgetableView {
protected:
    /** The interactive button */
    std::shared_ptr<cugl::scene2::Button> _button;
    
    /** The button's visual node */
    std::shared_ptr<cugl::scene2::PolygonNode> _buttonNode;
    
    /** Button radius */
    float _buttonRadius;
    
    /**
     * Creates the visual content for this fidgetable.
     */
    void buildContent() override;
    
    /**
     * Called when the button is pressed.
     */
    virtual void onPressed();
    
public:
    F8karting();
    virtual ~F8karting();
    
    bool init(int index, const cugl::Size& pageSize) override;
    static std::shared_ptr<F8karting> alloc(const cugl::Size& pageSize);
    void dispose() override;
    void update(float timestep) override;
    void setActive(bool active) override;
    void activateInputs() override;
    void deactivateInputs() override;
};

#endif /* __F8KARTING_H__ */

