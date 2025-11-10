#ifndef OH_NATIVE_INTEROP_WRAP_VIEW_H
#define OH_NATIVE_INTEROP_WRAP_VIEW_H

#include <functional>
#include <memory>
#include "../render_node/oh_base_render_node.h"

namespace OH {
    class InteropWrapView{
    public:
       // using SizeChangeCallback = std::function<void(float width, float height)>;
        struct Rect {
            float x;
            float y;
            float width;
            float height;
        };
        
        InteropWrapView();
        ~InteropWrapView();

        BaseRenderNode* getBaseRenderNodePtr();
        void setUserInteraction(bool interactionEnable);

        
        // 属性
        //void setActualAccessibilityContainer(std::shared_ptr<UIView> container);
        //std::shared_ptr<UIView> getActualAccessibilityContainer() const;
        
        // 公共方法
        //void bindComposeInteropContainer(std::shared_ptr<UIView> view);
        //void setOnSizeChange(SizeChangeCallback callback);
        
  
        //void layoutSubviews();
        //void addSubview(std::shared_ptr<UIView> view);
        //std::shared_ptr<UIView> hitTest(const CGPoint& point, const UIEvent* event);
        //std::shared_ptr<UIView> accessibilityContainer();

    private:
        //void prepareForScrollViewIfNeeded();
        //void addFrameListener(std::shared_ptr<UIView> child);
        //void removeFrameListener();
        //void handleFrameChange(const CGRect& newFrame);
        
        // 成员变量
        //std::shared_ptr<TMMInteropScrollView> interopScrollView_;
       //std::shared_ptr<UIView> lastChild_;
        Rect lastFrame_;
        std::unique_ptr<BaseRenderNode> renderNode_ =  std::make_unique<OH::BaseRenderNode>();
        // SizeChangeCallback onSizeChange_;
       // std::shared_ptr<UIView> actualAccessibilityContainer_;
        
        // KVO 观察者标记
       // void* frameObserverContext_;
    };
} // namespace OH

#endif // OH_NATIVE_INTEROP_WRAP_VIEW_H