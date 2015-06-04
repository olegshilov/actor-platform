//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: /Users/ex3ndr/Develop/actor-model/library/actor-cocoa-base/build/java/im/actor/model/api/rpc/RequestSignUp.java
//

#ifndef _APRequestSignUp_H_
#define _APRequestSignUp_H_

#include "J2ObjC_header.h"
#include "im/actor/model/network/parser/Request.h"

@class BSBserValues;
@class BSBserWriter;
@class IOSByteArray;

#define APRequestSignUp_HEADER 4

@interface APRequestSignUp : APRequest

#pragma mark Public

- (instancetype)init;

- (instancetype)initWithLong:(jlong)phoneNumber
                withNSString:(NSString *)smsHash
                withNSString:(NSString *)smsCode
                withNSString:(NSString *)name
               withByteArray:(IOSByteArray *)deviceHash
                withNSString:(NSString *)deviceTitle
                     withInt:(jint)appId
                withNSString:(NSString *)appKey
                 withBoolean:(jboolean)isSilent;

+ (APRequestSignUp *)fromBytesWithByteArray:(IOSByteArray *)data;

- (jint)getAppId;

- (NSString *)getAppKey;

- (IOSByteArray *)getDeviceHash;

- (NSString *)getDeviceTitle;

- (jint)getHeaderKey;

- (NSString *)getName;

- (jlong)getPhoneNumber;

- (NSString *)getSmsCode;

- (NSString *)getSmsHash;

- (jboolean)isSilent;

- (void)parseWithBSBserValues:(BSBserValues *)values;

- (void)serializeWithBSBserWriter:(BSBserWriter *)writer;

- (NSString *)description;

@end

J2OBJC_EMPTY_STATIC_INIT(APRequestSignUp)

J2OBJC_STATIC_FIELD_GETTER(APRequestSignUp, HEADER, jint)

FOUNDATION_EXPORT APRequestSignUp *APRequestSignUp_fromBytesWithByteArray_(IOSByteArray *data);

FOUNDATION_EXPORT void APRequestSignUp_initWithLong_withNSString_withNSString_withNSString_withByteArray_withNSString_withInt_withNSString_withBoolean_(APRequestSignUp *self, jlong phoneNumber, NSString *smsHash, NSString *smsCode, NSString *name, IOSByteArray *deviceHash, NSString *deviceTitle, jint appId, NSString *appKey, jboolean isSilent);

FOUNDATION_EXPORT APRequestSignUp *new_APRequestSignUp_initWithLong_withNSString_withNSString_withNSString_withByteArray_withNSString_withInt_withNSString_withBoolean_(jlong phoneNumber, NSString *smsHash, NSString *smsCode, NSString *name, IOSByteArray *deviceHash, NSString *deviceTitle, jint appId, NSString *appKey, jboolean isSilent) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT void APRequestSignUp_init(APRequestSignUp *self);

FOUNDATION_EXPORT APRequestSignUp *new_APRequestSignUp_init() NS_RETURNS_RETAINED;

J2OBJC_TYPE_LITERAL_HEADER(APRequestSignUp)

typedef APRequestSignUp ImActorModelApiRpcRequestSignUp;

#endif // _APRequestSignUp_H_
