#include "oh_render_node_manager.h"
#include "xcomponent_log.h"
#include "native_node_api.h"
#include <window_manager/oh_display_manager.h>

void OHRenderNodeManager::DestroyNativeRoot() {
    if (m_contentHandle && m_customNodeHandle) {
        OH_ArkUI_NodeContent_RemoveNode(m_contentHandle, m_customNodeHandle);
    }
    OH_ArkUI_RenderNodeUtils_RemoveRenderNode(m_customNodeHandle, m_renderRootNode->getHandle());
    NativeNodeApi::getInstance()->disposeNode(m_customNodeHandle);
}

void OHRenderNodeManager::onResize(int32_t width, int32_t height) {
    float scaledDensity;

    ArkUI_NumberValue widthValue[] = {
            static_cast<float>(width)};
    ArkUI_AttributeItem widthItem = {
            widthValue, sizeof(widthValue) / sizeof(ArkUI_NumberValue)};

    NativeNodeApi::getInstance()->setLengthMetricUnit(m_customNodeHandle, ArkUI_LengthMetricUnit::ARKUI_LENGTH_METRIC_UNIT_PX);
    NativeNodeApi::getInstance()->setAttribute(m_customNodeHandle, NODE_WIDTH, &widthItem);

    ArkUI_NumberValue heightValue[] = {
            static_cast<float>(height)};
    ArkUI_AttributeItem heightItem = {
            heightValue, sizeof(heightValue) / sizeof(ArkUI_NumberValue)};

    NativeNodeApi::getInstance()->setAttribute(m_customNodeHandle, NODE_HEIGHT, &heightItem);
    m_renderRootNode->setSize(static_cast<int32_t>(width), static_cast<int32_t>(height));
}

void OHRenderNodeManager::CreateNativeRoot(napi_env env, napi_value nodeContent) {
    auto result = OH_ArkUI_GetNodeContentFromNapiValue(env, nodeContent, &m_contentHandle);
    if (result != ARKUI_ERROR_CODE_NO_ERROR || m_contentHandle == nullptr) {
        LOGE("Failed to get node content from napi value");
        return;
    }

    m_customNodeHandle = NativeNodeApi::getInstance()->createNode(ARKUI_NODE_CUSTOM);
    if (m_customNodeHandle == nullptr) {
        LOGE("Failed to create custom node");
        return;
    }

    m_renderRootNode = std::make_unique<OH::BaseRenderNode>();
    OH_ArkUI_RenderNodeUtils_AddRenderNode(m_customNodeHandle, m_renderRootNode->getHandle());
    OH_ArkUI_NodeContent_AddNode(m_contentHandle, m_customNodeHandle);
    LOGI("Create native root successfully");
}

arkui_utils::OHNativeCanvasProxyFactory* OHRenderNodeManager::createNativeCanvasProxyFactory() {
    if (m_renderRootNode == nullptr) {
        LOGE("Render root node is null. Cannot create proxy factory.");
        return nullptr;
    }

    if (!m_canvasProxyFactory) {
        m_canvasProxyFactory = std::make_unique<arkui_utils::OHNativeCanvasProxyFactory>(m_renderRootNode.get());
    }
    return m_canvasProxyFactory.get();
}


napi_value OHRenderNodeManager::stringToNAPIValue(napi_env env, const char* str) {
    napi_value result;
    napi_status status;

    if (str == NULL) {
        napi_get_null(env, &result);
        return result;
    }

    status = napi_create_string_utf8(env, str, NAPI_AUTO_LENGTH, &result);
    if (status != napi_ok) {
        napi_get_undefined(env, &result);
    }

    return result;
}

napi_value OHRenderNodeManager::callArkUIVIewMethod(napi_env env, napi_value object, const char* method_name,
        size_t argc, napi_value* argv) {
    napi_value method;
    napi_value method_key;

    napi_create_string_utf8(env, method_name, NAPI_AUTO_LENGTH, &method_key);
    napi_get_property(env, object, method_key, &method);

    napi_valuetype value_type;
    napi_typeof(env, method, &value_type);

    if (value_type != napi_function) {
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    napi_value result;
    napi_call_function(env, object, method, argc, argv, &result);

    return result;
}

napi_value OHRenderNodeManager::getArkUIViewProperty(napi_env env, napi_value object, const char* property_name) {
    napi_value property_value;
    napi_value key;

    napi_create_string_utf8(env, property_name, NAPI_AUTO_LENGTH, &key);

    napi_status status = napi_get_property(env, object, key, &property_value);

    if (status != napi_ok) {
        napi_get_undefined(env, &property_value);
    }

    return property_value;
}

void OHRenderNodeManager::CreateArkUIView(napi_env env, napi_value createArkUiViewCallback) {
    m_env = env;
    napi_create_reference(env, createArkUiViewCallback, 1, &m_createArkUIView);
}

napi_value OHRenderNodeManager::CreateMixedNode(const char* name, napi_value parameter) {
    napi_handle_scope scope;
    napi_open_handle_scope(m_env, &scope);
    napi_value result = nullptr;
    napi_value composeName = stringToNAPIValue(m_env, name);
    napi_value argv[2] = {composeName, parameter};
    napi_value createArkUIView = nullptr;
    napi_get_reference_value(m_env, m_createArkUIView, &createArkUIView);

    napi_call_function(m_env, nullptr, createArkUIView, 2, argv, &result);
    auto view = getArkUIViewProperty(m_env, result, "frameNode");
    LOGI("xxxTest getArkUIViewProperty = %{public}p", view);
    OH_ArkUI_GetNodeHandleFromNapiValue(m_env, view, &m_mixedHandle);
    LOGI("xxxTest m_mixedHandle = %{public}p", m_mixedHandle);
    NativeNodeApi::getInstance()->addChild(m_customNodeHandle, m_mixedHandle);
    return result;
}



