//
//  EaseFlex.h
//  Ease
//
//  Created by skynet on 2019/8/14.
//  Copyright © 2019 huayang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EaseFlexDefinitions.h"

NS_ASSUME_NONNULL_BEGIN
// FlexLayout的oc改装版本

#define EaseFlexReadonlyCopyProperty @property (nonatomic, copy, readonly)

@class EaseFlex;
typedef void(^EaseFlexDefine)(EaseFlex *flex);

@interface EaseFlex : NSObject

@property (nonatomic, weak) UIView *view; // Flex items's UIView.
/**
 Item natural size, considering only properties of the view itself. Independent of the item frame.
 */
@property (nonatomic, readonly) CGSize intrinsicSize;

/**
 This property controls dynamically if a flexbox's UIView is included or not in the flexbox layouting. When a
 flexbox's UIView is excluded, FlexLayout won't layout the view and its children views.
 */
@property (nonatomic, assign) BOOL isIncludedInLayout;

- (instancetype)initWithView:(UIView *)view;

#pragma mark - Flex item addition and definition

/**
 This method adds a flex item (UIView) to a flex container. Internally the methods adds the UIView has subviews and enables flexbox.
 
 - Returns: The added view flex interface
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^addItem)(void);

/**
 This method is similar to `addItem(: UIView)` except that it also creates the flex item's UIView. Internally the method creates an
 UIView, adds it has subviews and enables flexbox. This is useful to add a flex item/container easily when you don't need to refer to it later.
 
 - Parameter view: view to add to the flex container
 - Returns: The added view flex interface
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^addItemView)(UIView *);

/**
 This method is used to structure your code so that it matches the flexbox structure. The method has a closure parameter with a
 single parameter called `flex`. This parameter is in fact, the view's flex interface, it can be used to adds other flex items
 and containers.
 
 - Parameter closure:
 - Returns: Flex interface
 */
//- (EaseFlex * (^)(EaseFlexDefine))define;
@property (nonatomic, copy, readonly) EaseFlex * (^define)(EaseFlexDefine);

#pragma mark - Layout / intrinsicSize / sizeThatFits

/**
 The method layout the flex container's children
 
 - Parameter mode: specify the layout mod (LayoutMode).
 */
- (void)layoutWithMode:(EaseFlexLayoutMode)mode;
/**
 Layout with .FitContainer mode
 */
- (void)layout;

/**
 This method controls dynamically if a flexbox's UIView is included or not in the flexbox layouting. When a
 flexbox's UIView is excluded, FlexLayout won't layout the view and its children views.
 
 - Parameter included: true to layout the view
 - Returns:
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^flex_isIncludedInLayout)(BOOL);

/**
 The framework is so highly optimized, that flex item are layouted only when a flex property is changed and when flex container
 size change. In the event that you want to force FlexLayout to do a layout of a flex item, you can mark it as dirty
 using `markDirty()`.
 
 Dirty flag propagates to the root of the flexbox tree ensuring that when any item is invalidated its whole subtree will be re-calculated
 
 - Returns: Flex interface
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^markDirty)(void);

/**
 Returns the item size when layouted in the specified frame size
 
 - Parameter size: frame size
 - Returns: item size
 */
- (CGSize)sizeThatFits:(CGSize)size;

#pragma mark - Direction, wrap, flow

/**
 The `direction` property establishes the main-axis, thus defining the direction flex items are placed in the flex container.
 
 The `direction` property specifies how flex items are laid out in the flex container, by setting the direction of the flex
 container’s main axis. They can be laid out in two main directions,  like columns vertically or like rows horizontally.
 
 Note that row and row-reverse are affected by the layout direction (see `layoutDirection` property) of the flex container.
 If its text direction is LTR (left to right), row represents the horizontal axis oriented from left to right, and row-reverse
 from right to left; if the direction is rtl, it's the opposite.
 
 - Parameter value: Default value is .column
 适用于父类容器的元素上
 
 设置或检索伸缩盒对象的子元素在父容器中的位置。
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^direction)(EaseFlexDirection);

/**
 The `wrap` property controls whether the flex container is single-lined or multi-lined, and the direction of the cross-axis, which determines the direction in which the new lines are stacked in.
 
 - Parameter value: Default value is .noWrap
 适用于父类容器上
 
 设置或检索伸缩盒对象的子元素超出父容器时是否换行。
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^wrap)(EaseFlexWrapMode);

/**
 Direction defaults to Inherit on all nodes except the root which defaults to LTR. It is up to you to detect the
 user’s preferred direction (most platforms have a standard way of doing this) and setting this direction on the
 root of your layout tree.
 
 - Parameter value: new LayoutDirection
 - Returns:
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^layoutDirection)(EaseFlexLayoutDirection);

#pragma mark - justity, alignment, position

/**
 The `justifyContent` property defines the alignment along the main-axis of the current line of the flex container.
 It helps distribute extra free space leftover when either all the flex items on a line have reached their maximum
 size. For example, if children are flowing vertically, `justifyContent` controls how they align vertically.
 
 - Parameter value: Default value is .start
 
 适用于父类容器上
 
 设置或检索弹性盒子元素在主轴（横轴）方向上的对齐方式。
 
 当弹性盒里一行上的所有子元素都不能伸缩或已经达到其最大值时，
 这一属性可协助对多余的空间进行分配。当元素溢出某行时，这一属性同样会在对齐上进行控制
 
 if direction is row
 start:口口....
 center:..口口..
 end:....口口
 spaceAround:..口....口..
 spaceEvenly:..口..口..
 spaceBetween:口....口
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^justifyContent)(EaseFlexJustifyContent);

/**
 The `alignItems` property defines how flex items are laid out along the cross axis on the current line.
 Similar to `justifyContent` but for the cross-axis (perpendicular to the main-axis). For example, if
 children are flowing vertically, `alignItems` controls how they align horizontally.
 
 - Parameter value: Default value is .stretch
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^alignItems)(EaseFlexAlignItems);

/**
 The `alignSelf` property controls how a child aligns in the cross direction, overriding the `alignItems`
 of the parent. For example, if children are flowing vertically, `alignSelf` will control how the flex item
 will align horizontally.
 
 - Parameter value: Default value is .auto
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^alignSelf)(EaseFlexAlignSelf);

/**
 The align-content property aligns a flex container’s lines within the flex container when there is extra space
 in the cross-axis, similar to how justifyContent aligns individual items within the main-axis.
 
 - Parameter value: Default value is .start
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^alignContent)(EaseFlexAlignContent);

#pragma mark - grow / shrink / basis

/**
 The `grow` property defines the ability for a flex item to grow if necessary. It accepts a unitless value
 that serves as a proportion. It dictates what amount of the available space inside the flex container the
 item should take up.
 
 - Parameter value: Default value is 0
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^grow)(CGFloat);

/**
 It specifies the "flex shrink factor", which determines how much the flex item will shrink relative to the
 rest of the flex items in the flex container when there isn't enough space on the main-axis.
 
 When omitted, it is set to 0 and the flex shrink factor is multiplied by the flex `basis` when distributing
 negative space.
 
 A shrink value of 0 keeps the view's size in the main-axis direction. Note that this may cause the view to
 overflow its flex container.
 
 - Parameter value: Default value is 1
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^shrink)(CGFloat);

/**
 This property takes the same values as the width and height properties, and specifies the initial size of the
 flex item, before free space is distributed according to the grow and shrink factors.
 
 Specifying `nil` set the basis as `auto`, which means the length is equal to the length of the item. If the
 item has no length specified, the length will be according to its content.
 
 - Parameter value: Default value is 0
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^autoBasis)(void);

/**
 This property takes the same values as the width and height properties, and specifies the initial size of the
 flex item, before free space is distributed according to the grow and shrink factors.
 
 Specifying `nil` set the basis as `auto`, which means the length is equal to the length of the item. If the
 item has no length specified, the length will be according to its content.
 
 - Parameter value: Default value is 0
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^basis)(CGFloat);

#pragma mark - Dimension / width / height / size

/**
 The value specifies the view's width in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^autoWidth)(void);

/**
 The value specifies the view's width in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^width)(CGFloat);

/**
 The value specifies the view's width in percentage of its container width. The value must be non-negative.
 Example: view.flex.width(20%)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^widthWithPercent)(CGFloat);

/**
 The value specifies the view's height in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^autoHeight)(void);

/**
 The value specifies the view's height in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^height)(CGFloat);

/**
 The value specifies the view's height in percentage of its container height. The value must be non-negative.
 Example: view.flex.height(40%)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^heightWithPercent)(CGFloat);

/**
 The value specifies view's width and the height in pixels. Values must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^autoSize)(void);

/**
 The value specifies view's width and the height in pixels. Values must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^size)(CGSize);

/**
 The value specifies the width and the height of the view in pixels, creating a square view. Values must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^sideLength)(CGFloat);

/**
 Set minWidth to undefined
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^undefinedMinWidth)(void);

/**
 The value specifies the view's minimum width in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^minWidth)(CGFloat);

/**
 The value specifies the view's minimum width in percentage of its container width. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^minWidthWithPercent)(CGFloat);

/**
 Set maxWidth to undefined
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^undefinedMaxWidth)(void);

/**
 The value specifies the view's maximum width in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^maxWidth)(CGFloat);

/**
 The value specifies the view's maximum width in percentage of its container width. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^maxWidthWithPercent)(CGFloat);

/**
 Set minHeight to undefined
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^undefinedMinHeight)(void);

/**
 The value specifies the view's minimum height in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^minHeight)(CGFloat);

/**
 The value specifies the view's minimum height in percentage of its container height. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^minHeightWithPercent)(CGFloat);

/**
 Set maxHeight to undefined
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^undefinedMaxHeight)(void);

/**
 The value specifies the view's maximum height in pixels. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^maxHeight)(CGFloat);

/**
 The value specifies the view's maximum height in percentage of its container height. The value must be non-negative.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^maxHeightWithPercent)(CGFloat);

/**
 Set aspectRatio to undefined
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^undefinedAspectRatio)(void);

/**
 AspectRatio is a property introduced by Yoga that don't exist in CSS. AspectRatio solves the problem of knowing
 one dimension of an element and an aspect ratio, this is very common when it comes to images, videos, and other
 media types. AspectRatio accepts any floating point value > 0, the default is undefined.
 
 - Parameter value:
 - Returns:
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^aspectRatio)(CGFloat);

/**
 AspectRatio is a property introduced by Yoga that don't exist in CSS. AspectRatio solves the problem of knowing
 one dimension of an element and an aspect ratio, this is very common when it comes to images, videos, and other
 media types. AspectRatio accepts any floating point value > 0, the default is undefined.
 
 - Parameter value:
 - Returns:
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^aspectRatioOfImageView)(UIImageView *);

#pragma mark - Absolute positionning

/**
 The position property tells Flexbox how you want your item to be positioned within its parent.
 
 - Parameter value: Default value is .relative
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^position)(EaseFlexPosition);

/**
 Set the left edge distance from the container left edge in pixels.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^left)(CGFloat);

/**
 Set the left edge distance from the container left edge in percentage of its container width.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^leftWithPercent)(CGFloat);

/**
 Set the top edge distance from the container top edge in pixels.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^top)(CGFloat);

/**
 Set the top edge distance from the container top edge in percentage of its container height.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^topWithPercent)(CGFloat);

/**
 Set the right edge distance from the container right edge in pixels.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^right)(CGFloat);

/**
 Set the right edge distance from the container right edge in percentage of its container width.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^rightWithPercent)(CGFloat);

/**
 Set the bottom edge distance from the container bottom edge in pixels.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^bottom)(CGFloat);

/**
 Set the bottom edge distance from the container bottom edge in percentage of its container height.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^bottomWithPercent)(CGFloat);

/**
 Set the start edge (LTR=left, RTL=right) distance from the container start edge in pixels.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^start)(CGFloat);

/**
 Set the start edge (LTR=left, RTL=right) distance from the container start edge in
 percentage of its container width.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^startWithPercent)(CGFloat);

/**
 Set the end edge (LTR=right, RTL=left) distance from the container end edge in pixels.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^end)(CGFloat);

/**
 Set the end edge (LTR=right, RTL=left) distance from the container end edge in
 percentage of its container width.
 This method is valid only when the item position is absolute (`view.flex.position(.absolute)`)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^endWithPercent)(CGFloat);

#pragma mark - Margin

/**
 Set the top margin. Top margin specify the offset the top edge of the item should have from it’s closest sibling (item) or parent (container).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginTop)(CGFloat);

/**
 Set margin top with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginTopWithPercent)(CGFloat);

/**
 Set the left margin. Left margin specify the offset the left edge of the item should have from it’s closest sibling (item) or parent (container).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginLeft)(CGFloat);

/**
 Set margin left with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginLeftWithPercent)(CGFloat);

/**
 Set the bottom margin. Bottom margin specify the offset the bottom edge of the item should have from it’s closest sibling (item) or parent (container).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginBottom)(CGFloat);

/**
 Set margin bottom with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginBottomWithPercent)(CGFloat);

/**
 Set the right margin. Right margin specify the offset the right edge of the item should have from it’s closest sibling (item) or parent (container).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginRight)(CGFloat);

/**
 Set margin right with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginRightWithPercent)(CGFloat);

/**
 Set the start margin.
 
 Depends on the item `LayoutDirection`:
 * In LTR direction, start margin specify the offset the **left** edge of the item should have from it’s closest sibling (item) or parent (container).
 * IN RTL direction, start margin specify the offset the **right** edge of the item should have from it’s closest sibling (item) or parent (container).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginStart)(CGFloat);

/**
 Set margin start with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginStartWithPercent)(CGFloat);

/**
 Set the end margin.
 
 Depends on the item `LayoutDirection`:
 * In LTR direction, end margin specify the offset the **right** edge of the item should have from it’s closest sibling (item) or parent (container).
 * IN RTL direction, end margin specify the offset the **left** edge of the item should have from it’s closest sibling (item) or parent (container).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginEnd)(CGFloat);

/**
 Set margin end with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginEndWithPercent)(CGFloat);

/**
 Set the left, right, start, end to the specified value.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginHorizontal)(CGFloat);

/**
 Set margin horizontal with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginHorizontalWithPercent)(CGFloat);

/**
 Set the top and bottom margins to the specified value.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginVertical)(CGFloat);

/**
 Set margin vertical with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginVerticalWithPercent)(CGFloat);

/**
 Set all margins using UIEdgeInsets.
 This method is particularly useful to set all margins using iOS 11 `UIView.safeAreaInsets`.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginWithInsets)(UIEdgeInsets);

/**
 Set margins using NSDirectionalEdgeInsets.
 This method is particularly to set all margins using iOS 11 `UIView.directionalLayoutMargins`.
 
 Available only on iOS 11 and higher.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginWithDirectionalInsets)(NSDirectionalEdgeInsets) NS_AVAILABLE_IOS(11_0);

/**
 Set all margins to the specified value.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^margin)(CGFloat);

/**
 Set margin with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginWithPercent)(CGFloat);

/**
 Set the individually vertical margins (top, bottom) and horizontal margins (left, right, start, end).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginVH)(CGFloat, CGFloat);

/**
 Set margin horizontal and vertical with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginVHWithPercent)(CGFloat, CGFloat);

/**
 Set all margins (top, left, bottom, right)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginAll)(CGFloat, CGFloat, CGFloat, CGFloat);

/**
 Set all margins with percent value, for example, width is 90%, the value should be 90.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^marginAllWithPercent)(CGFloat, CGFloat, CGFloat, CGFloat);

#pragma mark - Padding

/**
 Set the top padding. Top padding specify the **offset children should have** from the container's top edge.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingTop)(CGFloat);

/**
 Set the left padding. Left padding specify the **offset children should have** from the container's left edge.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingLeft)(CGFloat);

/**
 Set the bottom padding. Bottom padding specify the **offset children should have** from the container's bottom edge.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingBottom)(CGFloat);

/**
 Set the right padding. Right padding specify the **offset children should have** from the container's right edge.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingRight)(CGFloat);

/**
 Set the start padding.
 
 Depends on the item `LayoutDirection`:
 * In LTR direction, start padding specify the **offset children should have** from the container's left edge.
 * IN RTL direction, start padding specify the **offset children should have** from the container's right edge.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingStart)(CGFloat);

/**
 Set the end padding.
 
 Depends on the item `LayoutDirection`:
 * In LTR direction, end padding specify the **offset children should have** from the container's right edge.
 * IN RTL direction, end padding specify the **offset children should have** from the container's left edge.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingEnd)(CGFloat);

/**
 Set the left, right, start and end paddings to the specified value.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingHorizontal)(CGFloat);

/**
 Set the top and bottom paddings to the specified value.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingVertical)(CGFloat);

/**
 Set paddings using UIEdgeInsets.
 This method is particularly useful to set all paddings using iOS 11 `UIView.safeAreaInsets`.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingWithInsets)(UIEdgeInsets);

/**
 Set paddings using NSDirectionalEdgeInsets.
 This method is particularly to set all paddings using iOS 11 `UIView.directionalLayoutMargins`.
 
 Available only on iOS 11 and higher.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingWithDirectionalInsets)(NSDirectionalEdgeInsets) NS_AVAILABLE_IOS(11_0);

/**
 Set all paddings to the specified value.
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^padding)(CGFloat);

/**
 Set the individually vertical paddings (top, bottom) and horizontal paddings (left, right, start, end).
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingVH)(CGFloat, CGFloat);

/**
 Set all paddings (top, left, bottom, right)
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^paddingAll)(CGFloat, CGFloat, CGFloat, CGFloat);

#pragma mark - UIView Visual properties

/**
 Set the view background color.
 
 - Parameter color: new color
 - Returns: flex interface
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^backgroundColor)(UIColor *);

#pragma mark - Display

/**
 Set the view display or not
 可以设置盒子视图是否显示，
 */
EaseFlexReadonlyCopyProperty EaseFlex * (^display)(EaseFlexDisplay);

@end

@interface UIView (EaseFlexLayout)

@property (nonatomic, readonly) EaseFlex *flex;

@end

NS_ASSUME_NONNULL_END

