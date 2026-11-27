#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CCTextInputNode.hpp>
class $modify(CCTextInputNode) {
    bool ccTouchBegan(CCTouch* touch, CCEvent* event) {
        auto size = getContentSize();
        auto anchorPointOffset = isIgnoreAnchorPointForPosition() ? CCPointZero : m_textField->getAnchorPoint();
        auto point = convertTouchToNodeSpace(touch) + ((m_textField->getAnchorPoint() - anchorPointOffset) * size);
        auto result = 0 <= point.x && point.x <= size.width && 0 <= point.y && point.y <= size.height;
        if (result) {
            onClickTrackNode(true);
            updateCursorPosition(touch->getLocation(), {{0, 0}, size});
        } else {
            onClickTrackNode(false);
        }

        return result;
    }

    bool onTextFieldInsertText(CCTextFieldTTF* pSender, const char* text, int nLen, enumKeyCodes keyCodes) {
        auto result = CCTextInputNode::onTextFieldInsertText(pSender, text, nLen, keyCodes);
        switch (keyCodes) {
            case KEY_Left:
            case KEY_Right:
            case KEY_Up:
            case KEY_Down:
            case KEY_Enter: return true;
            default: break;
        }
        return false;
    }
};
