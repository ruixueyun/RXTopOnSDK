//
//  RXTopOnInitManager.h
//  RXTopOnSDK
//
//  Created by root11 on 2024/5/24.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/AnyThinkSDK.h>
#import <AppTrackingTransparency/AppTrackingTransparency.h>

NS_ASSUME_NONNULL_BEGIN

@interface RXTopOnInitManager : NSObject

/**
 * 获取SDK实例（单例）
 */
+ (instancetype)sharedSDK;

/**
 * 初始化方法
 * @param appID - appid
 * @param appKey appkey
 * @param error - error
 */
- (BOOL)startWithAppID:(NSString *)appID
                appKey:(NSString *)appKey
                 error:(NSError**)error;

/**
 * 初始化方法
 * @param appID - appid
 * @param appKey appkey
 * @param sdkConfigure 各广告平台的网络设置类
 * @param error - error
 * 三方平台Configure    平台    是否必传
 ATMintegralConfigure    Mintegral    可选
 ATGDTConfigure    GDT    可选
 ATPangleConfigure    Pangle    可选
 ATVungleConfigure    Vungle    可选
 ATAdColonyConfigure    AdColony    可选
 ATMyTargetConfigure    MyTarget    可选
 ATFacebookConfigure    Meta    可选
 */
- (BOOL)startWithAppID:(NSString *)appID
                appKey:(NSString *)appKey
         sdkConfigures:(ATSDKConfiguration *)sdkConfigure
                 error:(NSError**)error;

/**
 * 设置是否打印日志，YES打印，NO不打印，默认为NO
 */
+ (void)setLogEnabled:(BOOL)logEnabled;

/**
 * 配合[RXTopOnInitManager setLogEnabled:YES]，检查应用完整性
 */
+ (void)integrationChecking;

/**
 * 针对App的自定义规则，对此App下面的所有Placement都会生效，iOS端提供了相关的key作为选择
 * Key                      Note        自定义后台对应的Key
 kATCustomDataUserIDKey    用户唯一标识    user_id
 kATCustomDataChannelKey    发布渠道        channel
 kATCustomDataSubchannelKey  发布子渠道    sub_channel
 kATCustomDataAgeKey        用户年龄           age
 kATCustomDataGenderKey        用户性别         gender
 kATCustomDataNumberOfIAPKey   应用内付费次数    iap_time
 kATCustomDataIAPAmountKey    应用内付费金额    iap_amount
 kATCustomDataIAPCurrencyKey  应用内付费币种，如美元 “USD” iap_currency
 */
- (void)customData:(NSDictionary *)customData;

/**
 * 针对某个广告位下，配置自定义规则，如参数中有key与App维度下相同，会优先使用Placement下面的内容
 * @param customData - 自定义规则，同‘customData:’中的key
 * @param placementID - 广告位 id
 */
- (void)setCustomData:(NSDictionary *)customData
       forPlacementID:(NSString *)placementID;

/**
 * 针对交叉推广设置排除已安装AppID的列表，被排除的AppID所对应的产品不会再被推广
 * 传入的AppleId与后台配置的交叉推广产品App Store ID一致才能成功过滤排除
 */
- (void)setExludeAppleIdArray:(NSArray *)appleIdArray;

/**
 * （1）SDK默认会收集用户的以下数据：
 操作系统、系统版本名、系统版本号、应用包名、应用版本名、应用版本号、设备品牌、设备型号、分辨率、屏幕方向、网络类型、移动网络代码、移动国家代码、系统语言、时区、IP地址、User Agent、IDFA、IDFV
 （2）当开发者的应用允许收集以上数据时，必须告知用户并获取用户同意收集隐私数据的授权后才能收集（请参考TopOn隐私合规指南），否则必须调用API限制该数据的上报
 （3）SDK提供了API给开发者去限制这些隐私数据上报，当开发者限制了上报的设备数据时可能会影响TopOn功能的正常使用，如：流量分组、交叉推广、TopOn ADX等功能，请开发者谨慎设置。
 * Key    Note
 kATDeviceDataInfoOSVersionNameKey    系统版本名
 kATDeviceDataInfoOSVersionCodeKey    系统版本号
 kATDeviceDataInfoPackageNameKey    应用包名
 kATDeviceDataInfoAppVersionNameKey    应用版本名
 kATDeviceDataInfoAppVersionCodeKey    应用版本号
 kATDeviceDataInfoBrandKey    设备品牌
 kATDeviceDataInfoModelKey    设备型号
 kATDeviceDataInfoScreenKey    屏幕分辨率
 kATDeviceDataInfoNetworkTypeKey    网络类型
 kATDeviceDataInfoMNCKey    移动网络代码
 kATDeviceDataInfoMCCKey    移动国家代码
 kATDeviceDataInfoLanguageKey    系统语言
 kATDeviceDataInfoTimeZoneKey    时区
 kATDeviceDataInfoUserAgentKey    User Agent
 kATDeviceDataInfoOrientKey    屏幕方向
 kATDeviceDataInfoIDFAKey    idfa
 kATDeviceDataInfoIDFVKey    idfv
 */
- (void)setDeniedUploadInfoArray:(NSArray *)uploadInfoArray;

/**
 * 开启个性化推荐，默认情况是全部开启广告个性化推荐，如果手动设置关闭之后则全部广告平台关闭个性化推荐。 针对海外平台，如果关闭个性化推荐，涉及用户隐私的数据将不会被收集，可能会影响广告平台功能的正常使用，请谨慎设置。
 * @param state ATPersonalizedAdStateType 开启个性化推荐 (默认);ATNonpersonalizedAdStateType 屏蔽个性化推荐
 */
- (void)setPersonalizedAdState:(ATPersonalizedAdState)state;

/*
过滤placementid中某一个广告源的加载
placementid 广告位id
unitIDArray 广告源id
*/
- (void)setExludePlacementid:(NSString *)placementid
                 unitIDArray:(NSArray <NSString *> *)unitIDArray;

/**
过滤placementid中某些平台的广告加载
placementid 广告位id
networkFirmIDArray 平台id数组；数组中内容 e.g. @(ATNetworkFirmIDTypeFacebook)、@(ATNetworkFirmIDTypeAdmob)
*/
- (void)setExludePlacementid:(NSString *)placementid
          networkFirmIDArray:(NSArray <NSNumber *> *)networkFirmIDArray;

/**
 设置平台类型
 */
- (void)setSystemPlatformType:(ATSystemPlatformType)type;

/**
 测试使用：设置测试的idfa，例如Meta广告测试设备等
 */
+ (void)setHeaderBiddingTestModeWithDeviceID:(NSString *)idfa;

/**
 测试使用：设置调试广告平台及相关广告类型、相关调试设备
 */
+ (void)setDebuggerConfig:(void(^_Nullable)(ATDebuggerConfig * _Nullable debuggerConfig))debuggerConfigBlock;

/**
 测试使用：设置相关设备（一般不使用）
 */
+ (void)setDeviceInfoConfig:(void(^_Nullable)(ATDeviceInfoConfig * _Nullable deviceInfoConfig))deviceInfoConfigBlock;

@end

NS_ASSUME_NONNULL_END
