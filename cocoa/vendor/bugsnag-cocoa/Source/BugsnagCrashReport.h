//
//  KSCrashReport.h
//  Bugsnag
//
//  Created by Simon Maynard on 11/26/14.
//
//

#import <Foundation/Foundation.h>

@class BugsnagConfiguration;

typedef NS_ENUM(NSUInteger, BSGSeverity) {
    BSGSeverityError,
    BSGSeverityWarning,
    BSGSeverityInfo,
};

/**
 *  Convert a string to a severity value
 *
 *  @param severity Intended severity value, such as info, warning, or error
 *
 *  @return converted severity level or BSGSeverityError if no conversion is found
 */
BSGSeverity BSGParseSeverity(NSString *_Nonnull severity);

/**
 *  Serialize a severity for JSON payloads
 *
 *  @param severity a severity
 *
 *  @return the equivalent string value
 */
NSString *_Nonnull BSGFormatSeverity(BSGSeverity severity);

@interface BugsnagCrashReport : NSObject

/**
 *  Create a new crash report from a JSON crash report generated by KSCrash
 *
 *  @param report a KSCrash JSON report
 *
 *  @return a Bugsnag crash report
 */
- (instancetype _Nonnull)initWithKSReport:(NSDictionary *_Nonnull)report;

/**
 *  Create a basic crash report from raw parts
 *
 *  @param name      The name of the exception
 *  @param message   The reason or message from the exception
 *  @param config    Bugsnag configuration
 *  @param metaData  additional data to attach to the report
 *  @param severity  severity of the error
 *
 *  @return a Bugsnag crash report
 */
- (instancetype _Nonnull)initWithErrorName:(NSString *_Nonnull)name
                              errorMessage:(NSString *_Nonnull)message
                             configuration:(BugsnagConfiguration *_Nonnull)config
                                  metaData:(NSDictionary *_Nonnull)metaData
                                  severity:(BSGSeverity)severity;

/**
 *  Serialize a crash report as a JSON payload
 *
 *  @param data top level report data, may need to be modified based on environment
 *
 *  @return a crash report
 */
- (NSDictionary *_Nonnull)serializableValueWithTopLevelData:
    (NSMutableDictionary *_Nonnull)data;

/**
 *  Whether this report should be sent, based on release stage information
 *  cached at crash time and within the application currently
 *
 *  @return YES if the report should be sent
 */
- (BOOL)shouldBeSent;

/**
 *  Prepend a custom stacktrace with a provided type to the crash report
 */
- (void)attachCustomStacktrace:(NSArray *_Nonnull)frames
                      withType:(NSString *_Nonnull)type;

/**
 *  The release stages used to notify at the time this report is captured
 */
@property (nonatomic, readwrite, copy, nullable) NSArray *notifyReleaseStages;
/**
 *  A loose representation of what was happening in the application at the time
 *  of the event
 */
@property (nonatomic, readwrite, copy, nullable) NSString *context;
/**
 *  The severity of the error generating the report
 */
@property (nonatomic, readwrite) BSGSeverity severity;
/**
 *  The release stage of the application
 */
@property (nonatomic, readwrite, copy, nullable) NSString *releaseStage;
/**
 *  The class of the error generating the report
 */
@property (nonatomic, readwrite, copy, nullable) NSString *errorClass;
/**
 *  The message of or reason for the error generating the report
 */
@property (nonatomic, readwrite, copy, nullable) NSString *errorMessage;
/**
 *  Customized hash for grouping this report with other errors
 */
@property (nonatomic, readwrite, copy, nullable) NSString *groupingHash;
/**
 *  Breadcrumbs from user events leading up to the error
 */
@property (nonatomic, readwrite, copy, nullable) NSArray *breadcrumbs;
/**
 *  Further information attached to an error report, where each top level key
 *  generates a section on bugsnag, displaying key/value pairs
 */
@property (nonatomic, readwrite, copy, nonnull) NSDictionary *metaData;
/**
 *  Property overrides
 */
@property(nonatomic, readonly, copy, nonnull) NSDictionary *overrides;
/**
 *  Number of frames to discard at the top of the stacktrace
 */
@property(nonatomic, readwrite) NSUInteger depth;
/**
 *  Raw error data
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary *error;
/**
 *  Device information such as OS name and version
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary *device;
/**
 *  Device state such as memory allocation at crash time
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary *deviceState;
/**
 *  App information such as the name, version, and bundle ID
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary *app;
/**
 *  Device state such as oreground status and run duration
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary *appState;
@end
