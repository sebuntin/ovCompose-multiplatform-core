

#include "oh_native_interop_wrap_node.h"
#include <iostream>
#include "../xcomponent_log.h"

namespace OH {
    //static void* kFrameObserverContext = &kFrameObserverContext;

    InteropWrapView::InteropWrapView() 
        : lastFrame_({0, 0, 0, 0})
        // , frameObserverContext_(kFrameObserverContext) 
    {
        renderNode_->setSize(100, 100)
        ->setBackgroundColor(0xFFFF0000);
        //TMMComposeMarkViewForVideoReport(this);
    }

    InteropWrapView::~InteropWrapView() {
        //removeFrameListener();
    }

    BaseRenderNode* InteropWrapView::getBaseRenderNodePtr() {
        return renderNode_.get();
    }

    void setUserInteraction(bool interactionEnable) {

    }

    // void InteropWrapView::layoutSubviews() {
    //     UIView::layoutSubviews();
    //     prepareForScrollViewIfNeeded();
    // }

    // void InteropWrapView::prepareForScrollViewIfNeeded() {
    //     if (!interopScrollView_) {
    //         return;
    //     }
        
    //     interopScrollView_->setFrame(this->getBounds());
        
    //     auto subviews = this->getSubviews();
    //     if (!subviews.empty() && subviews[0] != interopScrollView_) {
    //         this->sendSubviewToBack(interopScrollView_);
    //     }
    // }

    // void InteropWrapView::addSubview(std::shared_ptr<UIView> view) {
    //     if (interopScrollView_) {
    //         interopScrollView_->addSubview(view);
    //     } else {
    //         UIView::addSubview(view);
    //     }

    //     addFrameListener(view);
    // }

    // void InteropWrapView::addFrameListener(std::shared_ptr<UIView> child) {
    //     removeFrameListener();

    //     if (child) {
    //         // 在 C++ 中模拟 KVO，这里使用回调机制
    //         child->setFrameChangeCallback([this](const CGRect& newFrame) {
    //             handleFrameChange(newFrame);
    //         });
    //         lastChild_ = child;
    //     }
    // }

    // void InteropWrapView::removeFrameListener() {
    //     if (lastChild_) {
    //         lastChild_->setFrameChangeCallback(nullptr);
    //         lastChild_ = nullptr;
    //     }
    // }

    // void InteropWrapView::handleFrameChange(const CGRect& newFrame) {
    //     if (!CGRectEqualToRect(lastFrame_, newFrame)) {
    //         lastFrame_ = newFrame;
    //         if (onSizeChange_) {
    //             onSizeChange_(newFrame.size.width, newFrame.size.height);
    //         }
    //     }
    // }

    // void InteropWrapView::setOnSizeChange(SizeChangeCallback callback) {
    //     onSizeChange_ = callback;
    // }

    // std::shared_ptr<UIView> InteropWrapView::hitTest(const CGPoint& point, const UIEvent* event) {
    //     auto view = UIView::hitTest(point, event);
    //     if (view.get() == this) {
    //         return nullptr;
    //     }
    //     return view;
    // }

    // std::shared_ptr<UIView> InteropWrapView::accessibilityContainer() {
    //     return actualAccessibilityContainer_;
    // }

    // void InteropWrapView::setActualAccessibilityContainer(std::shared_ptr<UIView> container) {
    //     actualAccessibilityContainer_ = container;
    // }

    // std::shared_ptr<UIView> InteropWrapView::getActualAccessibilityContainer() const {
    //     return actualAccessibilityContainer_;
    // }

    // void InteropWrapView::bindComposeInteropContainer(std::shared_ptr<UIView> view) {
    //     if (interopScrollView_) {
    //         interopScrollView_->bindComposeInteropContainer(view);
    //     }
    // }

    // std::shared_ptr<TMMInteropScrollView> InteropWrapView::getInteropScrollView() {
    //     if (!interopScrollView_) {
    //         interopScrollView_ = std::make_shared<TMMInteropScrollView>();
    //         UIView::addSubview(interopScrollView_);
    //     }
    //     return interopScrollView_;
    // }
} // namespace OH