//
//  EaseFlexDefinitions.h
//  Ease
//
//  Created by skynet on 2019/8/14.
//  Copyright © 2019 huayang. All rights reserved.
//

#ifndef EaseFlexDefinitions_h
#define EaseFlexDefinitions_h

#import "YGLayout.h"

typedef NS_ENUM(int, EaseFlexDirection) {
    /// Default value. The flexible items are displayed vertically, as a column.
    EaseFlexDirectionColumn = YGFlexDirectionColumn,
    /// Same as column, but in reverse order
    EaseFlexDirectionColumnReverse = YGFlexDirectionColumnReverse,
    /// The flexible items are displayed horizontally, as a row.
    EaseFlexDirectionRow = YGFlexDirectionRow,
    /// Same as row, but in reverse order
    EaseFlexDirectionRowReverse = YGFlexDirectionRowReverse
};

typedef NS_ENUM(int, EaseFlexJustifyContent) {
    /// Default value. Items are positioned at the beginning of the container.
    EaseFlexJustifyContentStart = YGJustifyFlexStart,
    /// Items are positioned at the center of the container
    EaseFlexJustifyContentCenter = YGJustifyCenter,
    /// Items are positioned at the end of the container
    EaseFlexJustifyContentEnd = YGJustifyFlexEnd,
    /// Items are positioned with space between the lines
    EaseFlexJustifyContentSpaceBetween = YGJustifySpaceBetween,
    /// Items are positioned with space before, between, and after the lines
    EaseFlexJustifyContentSpaceAround = YGJustifySpaceAround,
    /// Items are positioned with space distributed evenly, items have equal space around them.
    EaseFlexJustifyContentSpaceEvenly = YGJustifySpaceEvenly,
};

typedef NS_ENUM(int, EaseFlexAlignContent) {
    /// Default value. Lines stretch to take up the remaining space
    EaseFlexAlignContentStretch = YGAlignStretch,
    /// Lines are packed toward the start of the flex container
    EaseFlexAlignContentStart = YGAlignFlexStart,
    /// Lines are packed toward the center of the flex container
    EaseFlexAlignContentCenter = YGAlignCenter,
    /// Lines are packed toward the end of the flex container
    EaseFlexAlignContentEnd = YGAlignFlexEnd,
    /// Lines are evenly distributed in the flex container
    EaseFlexAlignContentSpaceBetween = YGAlignSpaceBetween,
    /// Lines are evenly distributed in the flex container, with half-size spaces on either end
    EaseFlexAlignContentSpaceAround = YGAlignSpaceAround,
};

typedef NS_ENUM(int, EaseFlexAlignItems) {
    /// Default. Items are stretched to fit the container
    EaseFlexAlignItemsStretch = YGAlignStretch,
    /// Items are positioned at the beginning of the container
    EaseFlexAlignItemsStart = YGAlignFlexStart,
    /// Items are positioned at the center of the container
    EaseFlexAlignItemsCenter = YGAlignCenter,
    /// Items are positioned at the end of the container
    EaseFlexAlignItemsEnd = YGAlignFlexEnd,
    /// Items are positioned at the baseline of the container
    // Not currently supported by Yoga.
    //EaseFlexAlignItemsBaseline
};

typedef NS_ENUM(int, EaseFlexAlignSelf) {
    /// Default. The element inherits its parent container's align-items property, or "stretch" if it has no parent container
    EaseFlexAlignSelfAuto = YGAlignAuto,
    /// The element is positioned to fit the container
    EaseFlexAlignSelfStretch = YGAlignStretch,
    /// The element is positioned at the beginning of the container
    EaseFlexAlignSelfStart = YGAlignFlexStart,
    /// The element is positioned at the center of the container
    EaseFlexAlignSelfCenter = YGAlignCenter,
    /// The element is positioned at the end of the container
    EaseFlexAlignSelfEnd = YGAlignFlexEnd,
    /// The element is positioned at the baseline of the container
    EaseFlexAlignSelfBaseline = YGAlignBaseline,
};

typedef NS_ENUM(int, EaseFlexWrapMode) {
    /// Default value. Specifies that the flexible items will not wrap
    EaseFlexNoWrap = YGWrapNoWrap,
    /// Specifies that the flexible items will wrap if necessary
    EaseFlexWrap = YGWrapWrap,
    /// Specifies that the flexible items will wrap, if necessary, in reverse order
    EaseFlexWrapReverse = YGWrapWrapReverse,
};

typedef NS_ENUM(int, EaseFlexPosition) {
    /// Default value.
    EaseFlexPositionRelative = YGPositionTypeRelative,
    /// Positioned absolutely in regards to its container. The item is positionned using properties top, bottom, left, right, start, end.
    EaseFlexPositionAbsolute = YGPositionTypeAbsolute,
};

typedef NS_ENUM(int, EaseFlexLayoutDirection) {
    /// Default value.
    EaseFlexLayoutDirectionInherit = YGDirectionInherit,
    /// Left to right layout direction
    EaseFlexLayoutDirectionLTR = YGDirectionLTR,
    /// Right to right layout direction
    EaseFlexLayoutDirectionRTL = YGDirectionRTL,
    /// Detected automatically
    //    EaseFlexLayoutDirectionAuto,
};

/**
 Defines how the `layout(mode:)` method layout its flex items.
 */
typedef NS_ENUM(NSUInteger, EaseFlexLayoutMode) {
    /// This is the default mode when no parameter is specified. Children are layouted **inside** the container's size (width and height).
    EaseFlexLayoutModeFitContainer,
    /// In this mode, children are layouted **using only the container's width**. The container's height will be adjusted to fit the flexbox's children
    EaseFlexLayoutModeAdjustHeight,
    /// In this mode, children are layouted **using only the container's height**. The container's width will be adjusted to fit the flexbox's children
    EaseFlexLayoutModeAdjustWidth,
};

typedef NS_ENUM(int, EaseFlexDisplay) {
    /// Default value
    EaseFlexDisplayFlex = YGDisplayFlex,
    /// With this value, the item will be hidden and not be calculated
    EaseFlexDisplayNone = YGDisplayNone,
};

#endif /* EaseFlexDefinitions_h */
