//
//  EaseFlex.m
//  Ease
//
//  Created by skynet on 2019/8/14.
//  Copyright © 2019 huayang. All rights reserved.
//

#import "EaseFlex.h"
#import <objc/runtime.h>
#import <YGLayout.h>
#import <UIView+Yoga.h>

@interface EaseFlex()

@property (nonatomic, strong) YGLayout *yoga;

@end

@implementation EaseFlex

#pragma mark - Properties

- (CGSize)intrinsicSize
{
    return _yoga.intrinsicSize;
}

#pragma mark - Lifecycle

- (instancetype)initWithView:(UIView *)view
{
    self = [super init];
    if (self) {
        self.view = view;
        self.yoga = view.yoga;
        
        // Enable flexbox and overwrite Yoga default values.
        _yoga.isEnabled = YES;
        _isIncludedInLayout = YES;
    }
    return self;
}

#pragma mark - Flex item addition and definition

- (EaseFlex * (^)(void))addItem
{
    return ^id(void) {
        UIView *view = [UIView new];
        return self.addItemView(view);
    };
}

- (EaseFlex * (^)(UIView *))addItemView
{
    return ^id(UIView *view) {
        NSAssert(self.view != nil, @"Trying to modify deallocated host view");
        
        [self.view addSubview:view];
        return view.flex;
    };
}

- (EaseFlex * (^)(EaseFlexDefine))define
{
    return ^id(EaseFlexDefine closure){
        closure(self);
        return self;
    };
}

#pragma mark - Layout / intrinsicSize / sizeThatFits

- (void)layout
{
    [self layoutWithMode:EaseFlexLayoutModeFitContainer];
}

/**
 The method layout the flex container's children
 
 - Parameter mode: specify the layout mod (LayoutMode).
 */
- (void)layoutWithMode:(EaseFlexLayoutMode)mode
{
    if (mode == EaseFlexLayoutModeFitContainer) {
        [_yoga applyLayoutPreservingOrigin:YES];
    } else {
        [_yoga applyLayoutPreservingOrigin:YES dimensionFlexibility:mode == EaseFlexLayoutModeAdjustWidth ? YGDimensionFlexibilityFlexibleWidth : YGDimensionFlexibilityFlexibleHeight];
    }
}

- (void)setIsIncludedInLayout:(BOOL)isIncludedInLayout
{
    _isIncludedInLayout = isIncludedInLayout;
    _yoga.isIncludedInLayout = isIncludedInLayout;
}

- (EaseFlex * (^)(BOOL))flex_isIncludedInLayout
{
    return ^id(BOOL included) {
        self.isIncludedInLayout = included;
        return self;
    };
}

- (EaseFlex * (^)(void))markDirty
{
    return ^id {
        [self.yoga markDirty];
        return self;
    };
}

- (CGSize)sizeThatFits:(CGSize)size
{
    return [_yoga calculateLayoutWithSize:size];
}

#pragma mark - Direction, wrap, flow

- (EaseFlex * (^)(EaseFlexDirection))direction
{
    return ^id(EaseFlexDirection value) {
        self.yoga.flexDirection = (YGFlexDirection)value;
        return self;
    };
}

- (EaseFlex * (^)(EaseFlexWrapMode))wrap
{
    return ^id(EaseFlexWrapMode value) {
        self.yoga.flexWrap = (YGWrap)value;
        return self;
    };
}

- (EaseFlex * (^)(EaseFlexLayoutDirection))layoutDirection
{
    return ^id(EaseFlexLayoutDirection value) {
        self.yoga.direction = (YGDirection)value;
        return self;
    };
}

#pragma mark - justity, alignment, position

- (EaseFlex * (^)(EaseFlexJustifyContent))justifyContent
{
    return ^id(EaseFlexJustifyContent value) {
        self.yoga.justifyContent = (YGJustify)value;
        return self;
    };
}

- (EaseFlex * (^)(EaseFlexAlignItems))alignItems
{
    return ^id(EaseFlexAlignItems value) {
        self.yoga.alignItems = (YGAlign)value;
        return self;
    };
}

- (EaseFlex * (^)(EaseFlexAlignSelf))alignSelf
{
    return ^id(EaseFlexAlignSelf value) {
        self.yoga.alignSelf = (YGAlign)value;
        return self;
    };
}

- (EaseFlex * (^)(EaseFlexAlignContent))alignContent
{
    return ^id(EaseFlexAlignContent value) {
        self.yoga.alignContent = (YGAlign)value;
        return self;
    };
}

#pragma mark - grow / shrink / basis

- (EaseFlex * (^)(CGFloat))grow
{
    return ^id(CGFloat value) {
        self.yoga.flexGrow = value;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))shrink
{
    return ^id(CGFloat value) {
        self.yoga.flexShrink = value;
        return self;
    };
}

- (EaseFlex * (^)(void))autoBasis
{
    return ^id(void) {
        self.yoga.flexBasis = YGValueAuto;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))basis
{
    return ^id(CGFloat value) {
        self.yoga.flexBasis = YGValueMake(value);
        return self;
    };
}

#pragma mark - Width / height / height

- (EaseFlex * (^)(void))autoWidth
{
    return ^id(void) {
        self.yoga.width = YGValueAuto;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))width
{
    return ^id(CGFloat value) {
        self.yoga.width = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))widthWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.width = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(void))autoHeight
{
    return ^id(void) {
        self.yoga.height = YGValueAuto;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))height
{
    return ^id(CGFloat value) {
        self.yoga.height = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))heightWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.height = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(void))autoSize
{
    return ^id(void) {
        self.yoga.width = YGValueAuto;
        self.yoga.height = YGValueAuto;
        return self;
    };
}

- (EaseFlex * (^)(CGSize))size
{
    return ^id(CGSize value) {
        self.yoga.width = YGValueMake(value.width);
        self.yoga.height = YGValueMake(value.height);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))sideLength
{
    return ^id(CGFloat value) {
        self.yoga.width = YGValueMake(value);
        self.yoga.height = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(void))undefinedMinWidth
{
    return ^id(void) {
        self.yoga.minWidth = YGValueUndefined;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))minWidth
{
    return ^id(CGFloat value) {
        self.yoga.minWidth = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))minWidthWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.minWidth = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(void))undefinedMaxWidth
{
    return ^id(void) {
        self.yoga.maxWidth = YGValueUndefined;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))maxWidth
{
    return ^id(CGFloat value) {
        self.yoga.maxWidth = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))maxWidthWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.maxWidth = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(void))undefinedMinHeight
{
    return ^id(void) {
        self.yoga.minHeight = YGValueUndefined;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))minHeight
{
    return ^id(CGFloat value) {
        self.yoga.minHeight = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))minHeightWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.minHeight = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(void))undefinedMaxHeight
{
    return ^id(void) {
        self.yoga.maxHeight = YGValueUndefined;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))maxHeight
{
    return ^id(CGFloat value) {
        self.yoga.maxHeight = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))maxHeightWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.maxHeight = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(void))undefinedAspectRatio
{
    return ^id(void) {
        self.yoga.aspectRatio = YGValueUndefined.value;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))aspectRatio
{
    return ^id(CGFloat value) {
        self.yoga.aspectRatio = value;
        return self;
    };
}

- (EaseFlex * (^)(UIImageView *))aspectRatioOfImageView
{
    return ^id(UIImageView *imageView) {
        if (imageView.image != nil) {
            CGSize imageSize = imageView.image.size;
            self.yoga.aspectRatio = imageSize.width / imageSize.height;
        }
        return self;
    };
}

#pragma mark - Absolute positionning

- (EaseFlex * (^)(EaseFlexPosition))position
{
    return ^id(EaseFlexPosition position) {
        self.yoga.position = (YGPositionType)position;
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))left
{
    return ^id(CGFloat value) {
        self.yoga.left = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))leftWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.left = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))top
{
    return ^id(CGFloat value) {
        self.yoga.top = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))topWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.top = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))right
{
    return ^id(CGFloat value) {
        self.yoga.right = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))rightWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.right = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))bottom
{
    return ^id(CGFloat value) {
        self.yoga.bottom = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))bottomWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.bottom = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))start
{
    return ^id(CGFloat value) {
        self.yoga.start = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))startWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.start = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))end
{
    return ^id(CGFloat value) {
        self.yoga.end = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))endWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.end = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

#pragma mark - Margin

- (EaseFlex * (^)(CGFloat))marginTop
{
    return ^id(CGFloat value) {
        self.yoga.marginTop = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginTopWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginTop = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginLeft
{
    return ^id(CGFloat value) {
        self.yoga.marginLeft = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginLeftWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginLeft = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginBottom
{
    return ^id(CGFloat value) {
        self.yoga.marginBottom = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginBottomWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginBottom = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginRight
{
    return ^id(CGFloat value) {
        self.yoga.marginRight = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginRightWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginRight = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginStart
{
    return ^id(CGFloat value) {
        self.yoga.marginStart = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginStartWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginStart = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginEnd
{
    return ^id(CGFloat value) {
        self.yoga.marginEnd = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginEndWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginEnd = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginHorizontal
{
    return ^id(CGFloat value) {
        self.yoga.marginHorizontal = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginHorizontalWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginHorizontal = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginVertical
{
    return ^id(CGFloat value) {
        self.yoga.marginVertical = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginVerticalWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.marginVertical = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(UIEdgeInsets))marginWithInsets
{
    return ^id(UIEdgeInsets insets) {
        self.yoga.marginTop = YGValueMake(insets.top);
        self.yoga.marginLeft = YGValueMake(insets.left);
        self.yoga.marginBottom = YGValueMake(insets.bottom);
        self.yoga.marginRight = YGValueMake(insets.right);
        return self;
    };
}

- (EaseFlex * (^)(NSDirectionalEdgeInsets))marginWithDirectionalInsets NS_AVAILABLE_IOS(11_0)
{
    return ^id(NSDirectionalEdgeInsets directionalInsets) {
        self.yoga.marginTop = YGValueMake(directionalInsets.top);
        self.yoga.marginStart = YGValueMake(directionalInsets.leading);
        self.yoga.marginBottom = YGValueMake(directionalInsets.bottom);
        self.yoga.marginEnd = YGValueMake(directionalInsets.trailing);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))margin
{
    return ^id(CGFloat value) {
        self.yoga.margin = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))marginWithPercent
{
    return ^id(CGFloat value) {
        self.yoga.margin = YGValueMakeWithUnit(value, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat, CGFloat))marginVH
{
    return ^id(CGFloat vertical, CGFloat horizontal) {
        self.yoga.marginVertical = YGValueMake(vertical);
        self.yoga.marginHorizontal = YGValueMake(horizontal);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat, CGFloat))marginVHWithPercent
{
    return ^id(CGFloat vertical, CGFloat horizontal) {
        self.yoga.marginVertical = YGValueMakeWithUnit(vertical, YGUnitPercent);
        self.yoga.marginHorizontal = YGValueMakeWithUnit(vertical, YGUnitPercent);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat, CGFloat, CGFloat, CGFloat))marginAll
{
    return ^id(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
        self.yoga.marginTop = YGValueMake(top);
        self.yoga.marginLeft = YGValueMake(left);
        self.yoga.marginBottom = YGValueMake(bottom);
        self.yoga.marginRight = YGValueMake(right);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat, CGFloat, CGFloat, CGFloat))marginAllWithPercent
{
    return ^id(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
        self.yoga.marginTop = YGValueMakeWithUnit(top, YGUnitPercent);
        self.yoga.marginLeft = YGValueMakeWithUnit(left, YGUnitPercent);
        self.yoga.marginBottom = YGValueMakeWithUnit(bottom, YGUnitPercent);
        self.yoga.marginRight = YGValueMakeWithUnit(right, YGUnitPercent);
        return self;
    };
}

#pragma mark - Padding

- (EaseFlex * (^)(CGFloat))paddingTop
{
    return ^id(CGFloat value) {
        self.yoga.paddingTop = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingLeft
{
    return ^id(CGFloat value) {
        self.yoga.paddingLeft = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingBottom
{
    return ^id(CGFloat value) {
        self.yoga.paddingBottom = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingRight
{
    return ^id(CGFloat value) {
        self.yoga.paddingRight = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingStart
{
    return ^id(CGFloat value) {
        self.yoga.paddingStart = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingEnd
{
    return ^id(CGFloat value) {
        self.yoga.paddingEnd = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingHorizontal
{
    return ^id(CGFloat value) {
        self.yoga.paddingHorizontal = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))paddingVertical
{
    return ^id(CGFloat value) {
        self.yoga.paddingVertical = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(UIEdgeInsets))paddingWithInsets
{
    return ^id(UIEdgeInsets value) {
        self.yoga.paddingTop = YGValueMake(value.top);
        self.yoga.paddingLeft = YGValueMake(value.left);
        self.yoga.paddingBottom = YGValueMake(value.bottom);
        self.yoga.paddingRight = YGValueMake(value.right);
        return self;
    };
}

- (EaseFlex * (^)(NSDirectionalEdgeInsets))paddingWithDirectionalInsets NS_AVAILABLE_IOS(11_0)
{
    return ^id(NSDirectionalEdgeInsets value) {
        self.yoga.paddingTop = YGValueMake(value.top);
        self.yoga.paddingStart = YGValueMake(value.leading);
        self.yoga.paddingBottom = YGValueMake(value.bottom);
        self.yoga.paddingEnd = YGValueMake(value.trailing);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat))padding
{
    return ^id(CGFloat value) {
        self.yoga.padding = YGValueMake(value);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat, CGFloat))paddingVH
{
    return ^id(CGFloat vertical, CGFloat horizontal) {
        self.yoga.paddingVertical = YGValueMake(vertical);
        self.yoga.paddingHorizontal = YGValueMake(horizontal);
        return self;
    };
}

- (EaseFlex * (^)(CGFloat, CGFloat, CGFloat, CGFloat))paddingAll
{
    return ^id(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
        self.yoga.paddingTop = YGValueMake(top);
        self.yoga.paddingLeft = YGValueMake(left);
        self.yoga.paddingBottom = YGValueMake(bottom);
        self.yoga.paddingRight = YGValueMake(right);
        return self;
    };
}

#pragma mark - UIView Visual properties

- (EaseFlex * (^)(UIColor *))backgroundColor
{
    return ^id(UIColor *color) {
        NSAssert(self.view != nil, @"Trying to modify deallocated host view");
        self.view.backgroundColor = color;
        return self;
    };
}

#pragma mark - Display

- (EaseFlex * (^)(EaseFlexDisplay))display
{
    return ^id(EaseFlexDisplay display) {
        self.yoga.display = (YGDisplay)display;
        return self;
    };
}

#pragma mark - Utility

YGValue YGValueMake(CGFloat value)
{
    YGValue ygValue; ygValue.value = value; ygValue.unit = YGUnitPoint; return ygValue;
}

YGValue YGValueMakeWithUnit(CGFloat value, YGUnit unit)
{
    YGValue ygValue; ygValue.value = value; ygValue.unit = unit; return ygValue;
}

@end

@implementation UIView (EaseFlexLayout)

- (EaseFlex *)flex
{
    EaseFlex *flex = objc_getAssociatedObject(self, @selector(flex));
    if (!flex) {
        flex = [[EaseFlex alloc] initWithView:self];
        objc_setAssociatedObject(self, @selector(flex), flex, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
    
    return flex;
}
@end
