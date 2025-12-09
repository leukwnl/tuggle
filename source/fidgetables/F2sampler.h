//
//  F2sampler.h
//  Tuggle
//
//  Second fidgetable toy - a single interactive button.
//

#ifndef __F2SAMPLER_H__
#define __F2SAMPLER_H__

#include "FidgetableView.h"

/**
 * Second fidgetable toy in the carousel.
 * Currently displays a single circular button.
 */
class F2sampler : public FidgetableView {
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
    F2sampler();
    virtual ~F2sampler();
    
    bool init(int index, const cugl::Size& pageSize) override;
    static std::shared_ptr<F2sampler> alloc(const cugl::Size& pageSize);
    void dispose() override;
    void update(float timestep) override;
    void setActive(bool active) override;
    void activateInputs() override;
    void deactivateInputs() override;
};

#endif /* __F2SAMPLER_H__ */

