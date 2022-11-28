cmake_minimum_required(VERSION 3.4.1)

project(chipmunk)

set(CHIPMUNK_SRC "src/chipmunk.c"
                 "src/constraints/cpConstraint.c"
                 "src/constraints/cpDampedRotarySpring.c"
                 "src/constraints/cpDampedSpring.c"
                 "src/constraints/cpGearJoint.c"
                 "src/constraints/cpGrooveJoint.c"
                 "src/constraints/cpPinJoint.c"
                 "src/constraints/cpPivotJoint.c"
                 "src/constraints/cpRatchetJoint.c"
                 "src/constraints/cpRotaryLimitJoint.c"
                 "src/constraints/cpSimpleMotor.c"
                 "src/constraints/cpSlideJoint.c"
                 "src/cpArbiter.c"
                 "src/cpArray.c"
                 "src/cpBB.c"
                 "src/cpBBTree.c"
                 "src/cpBody.c"
                 "src/cpCollision.c"
                 "src/cpHashSet.c"
                 "src/cpPolyShape.c"
                 "src/cpShape.c"
                 "src/cpSpace.c"
                 "src/cpSpaceComponent.c"
                 "src/cpSpaceHash.c"
                 "src/cpSpaceQuery.c"
                 "src/cpSpaceStep.c"
                 "src/cpSpatialIndex.c"
                 "src/cpSweep1D.c"
                 "src/cpVect.c")

add_library(${PROJECT_NAME} STATIC ${CHIPMUNK_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/chipmunk)
