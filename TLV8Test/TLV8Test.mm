//
//  TLV8Test.m
//  TLV8Test
//
//  Created by d. nye on 6/23/17.
//  Copyright © 2017 Mobile Flow LLC. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "tlv8.h"

@interface TLV8Test : XCTestCase

@end

@implementation TLV8Test

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    TLV8Class TLV8 = TLV8Class();
    

    struct tlv_map PairTagTLV8;
    memset(&PairTagTLV8, 0, sizeof(tlv_map));
    
    unsigned char buffer[11] = "\xff\x08testtest";

    TLV8.decode( buffer, 11, &PairTagTLV8 );

    XCTAssertTrue(PairTagTLV8.count == 1, @"Expected count 1, got %d", PairTagTLV8.count);
    XCTAssertTrue(PairTagTLV8.object[0].size == 8, @"Expected size 8, got %d", PairTagTLV8.object[0].size);
    XCTAssertTrue(PairTagTLV8.object[0].type == 0xf0, @"Expected type 0xf0, got %x", PairTagTLV8.object[0].type);
    
    unsigned char test[8] = "testing";
    XCTAssertTrue(PairTagTLV8.object[0].data == test, @"Expected data testing, got %s", PairTagTLV8.object[0].data);

}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
