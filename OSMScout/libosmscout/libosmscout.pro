TARGET = osmscout
TEMPLATE = lib
CONFIG += staticlib c++11
INCLUDEPATH += include 

macx {
    QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
    CONFIG +=c++11
}


SOURCES = \
          ../libosmscout/src/osmscout/AreaAreaIndex.cpp \
          ../libosmscout/src/osmscout/Area.cpp \
          ../libosmscout/src/osmscout/AreaNodeIndex.cpp \
          ../libosmscout/src/osmscout/AreaWayIndex.cpp \
          ../libosmscout/src/osmscout/Coord.cpp \
          ../libosmscout/src/osmscout/CoordDataFile.cpp \
          ../libosmscout/src/osmscout/Database.cpp \
          ../libosmscout/src/osmscout/DebugDatabase.cpp \
          ../libosmscout/src/osmscout/GeoCoord.cpp \
          ../libosmscout/src/osmscout/GroundTile.cpp \
          ../libosmscout/src/osmscout/Intersection.cpp \
          ../libosmscout/src/osmscout/Location.cpp \
          ../libosmscout/src/osmscout/LocationIndex.cpp \
          ../libosmscout/src/osmscout/LocationService.cpp \
          ../libosmscout/src/osmscout/Node.cpp \
          ../libosmscout/src/osmscout/NodeDataFile.cpp \
          ../libosmscout/src/osmscout/NumericIndex.cpp \
          ../libosmscout/src/osmscout/ObjectRef.cpp \
          ../libosmscout/src/osmscout/OptimizeAreasLowZoom.cpp \
          ../libosmscout/src/osmscout/OptimizeWaysLowZoom.cpp \
          ../libosmscout/src/osmscout/Path.cpp \
          ../libosmscout/src/osmscout/Pixel.cpp \
          ../libosmscout/src/osmscout/Point.cpp \
          ../libosmscout/src/osmscout/POIService.cpp \
          ../libosmscout/src/osmscout/Route.cpp \
          ../libosmscout/src/osmscout/RouteData.cpp \
          ../libosmscout/src/osmscout/RouteNode.cpp \
          ../libosmscout/src/osmscout/RoutePostprocessor.cpp \
          ../libosmscout/src/osmscout/RoutingProfile.cpp \
          ../libosmscout/src/osmscout/RoutingService.cpp \
          ../libosmscout/src/osmscout/SRTM.cpp \
          ../libosmscout/src/osmscout/Tag.cpp \
          #../libosmscout/src/osmscout/TextSearchIndex.cpp \
          ../libosmscout/src/osmscout/TurnRestriction.cpp \
          ../libosmscout/src/osmscout/TypeConfig.cpp \
          ../libosmscout/src/osmscout/TypeFeatures.cpp \
          ../libosmscout/src/osmscout/Types.cpp \
          ../libosmscout/src/osmscout/TypeSet.cpp \
          ../libosmscout/src/osmscout/WaterIndex.cpp \
          ../libosmscout/src/osmscout/Way.cpp \
          ../libosmscout/src/osmscout/util/Breaker.cpp \
          ../libosmscout/src/osmscout/util/Cache.cpp \
          ../libosmscout/src/osmscout/util/Color.cpp \
          ../libosmscout/src/osmscout/util/File.cpp \
          ../libosmscout/src/osmscout/util/FileScanner.cpp \
          ../libosmscout/src/osmscout/util/FileWriter.cpp \
          ../libosmscout/src/osmscout/util/GeoBox.cpp \
          ../libosmscout/src/osmscout/util/Geometry.cpp \
          ../libosmscout/src/osmscout/util/Logger.cpp \
          ../libosmscout/src/osmscout/util/Magnification.cpp \
          ../libosmscout/src/osmscout/util/NodeUseMap.cpp \
          ../libosmscout/src/osmscout/util/Number.cpp \
          ../libosmscout/src/osmscout/util/NumberSet.cpp \
          ../libosmscout/src/osmscout/util/Parser.cpp \
          ../libosmscout/src/osmscout/util/Progress.cpp \
          ../libosmscout/src/osmscout/util/Projection.cpp \
          ../libosmscout/src/osmscout/util/Reference.cpp \
          ../libosmscout/src/osmscout/util/StopClock.cpp \
          ../libosmscout/src/osmscout/util/String.cpp \
          ../libosmscout/src/osmscout/util/Tiling.cpp \
          ../libosmscout/src/osmscout/util/Transformation.cpp \
          ../libosmscout/src/osmscout/ost/Parser.cpp \
          ../libosmscout/src/osmscout/ost/Scanner.cpp \
          ../libosmscout/src/osmscout/system/SSEMath.cpp 

HEADERS = \
        ../libosmscout/include/osmscout/AreaAreaIndex.h \
        ../libosmscout/include/osmscout/AreaDataFile.h \
        ../libosmscout/include/osmscout/Area.h \
        ../libosmscout/include/osmscout/AreaNodeIndex.h \
        ../libosmscout/include/osmscout/AreaWayIndex.h \
        ../libosmscout/include/osmscout/CoordDataFile.h \
        ../libosmscout/include/osmscout/Coord.h \
        ../libosmscout/include/osmscout/CoreFeatures.h \
        ../libosmscout/include/osmscout/Database.h \
        ../libosmscout/include/osmscout/DataFile.h \
        ../libosmscout/include/osmscout/DebugDatabase.h \
        ../libosmscout/include/osmscout/GeoCoord.h \
        ../libosmscout/include/osmscout/GroundTile.h \
        ../libosmscout/include/osmscout/Intersection.h \
        ../libosmscout/include/osmscout/Location.h \
        ../libosmscout/include/osmscout/LocationIndex.h \
        ../libosmscout/include/osmscout/LocationService.h \
        ../libosmscout/include/osmscout/Navigation.h \
        ../libosmscout/include/osmscout/NodeDataFile.h \
        ../libosmscout/include/osmscout/Node.h \
        ../libosmscout/include/osmscout/NumericIndex.h \
        ../libosmscout/include/osmscout/ObjectRef.h \
        ../libosmscout/include/osmscout/OptimizeAreasLowZoom.h \
        ../libosmscout/include/osmscout/OptimizeWaysLowZoom.h \
        ../libosmscout/include/osmscout/Path.h \
        ../libosmscout/include/osmscout/Pixel.h \
        ../libosmscout/include/osmscout/Point.h \
        ../libosmscout/include/osmscout/POIService.h \
        ../libosmscout/include/osmscout/RouteData.h \
        ../libosmscout/include/osmscout/Route.h \
        ../libosmscout/include/osmscout/RouteNode.h \
        ../libosmscout/include/osmscout/RoutePostprocessor.h \
        ../libosmscout/include/osmscout/RoutingProfile.h \
        ../libosmscout/include/osmscout/RoutingService.h \
        ../libosmscout/include/osmscout/SRTM.h \
        ../libosmscout/include/osmscout/Tag.h \
        #../libosmscout/include/osmscout/TextSearchIndex.h \
        ../libosmscout/include/osmscout/TurnRestriction.h \
        ../libosmscout/include/osmscout/TypeConfig.h \
        ../libosmscout/include/osmscout/TypeFeatures.h \
        ../libosmscout/include/osmscout/TypeSet.h \
        ../libosmscout/include/osmscout/Types.h \
        ../libosmscout/include/osmscout/WaterIndex.h \
        ../libosmscout/include/osmscout/WayDataFile.h \
        ../libosmscout/include/osmscout/Way.h \
        ../libosmscout/include/osmscout/ost/Parser.h \
        ../libosmscout/include/osmscout/ost/Scanner.h \
        ../libosmscout/include/osmscout/private/Config.h \
        ../libosmscout/include/osmscout/private/CoreImportExport.h \
        ../libosmscout/include/osmscout/system/Assert.h \
        ../libosmscout/include/osmscout/system/Math.h \
        ../libosmscout/include/osmscout/system/SSEMath.h \
        ../libosmscout/include/osmscout/system/SSEMathPublic.h \
        ../libosmscout/include/osmscout/system/Types.h \
        ../libosmscout/include/osmscout/util/Breaker.h \
        ../libosmscout/include/osmscout/util/Cache.h \
        ../libosmscout/include/osmscout/util/Color.h \
        ../libosmscout/include/osmscout/util/File.h \
        ../libosmscout/include/osmscout/util/FileScanner.h \
        ../libosmscout/include/osmscout/util/FileWriter.h \
        ../libosmscout/include/osmscout/util/GeoBox.h \
        ../libosmscout/include/osmscout/util/Geometry.h \
        ../libosmscout/include/osmscout/util/Logger.h \
        ../libosmscout/include/osmscout/util/Magnification.h \
        ../libosmscout/include/osmscout/util/NodeUseMap.h \
        ../libosmscout/include/osmscout/util/Number.h \
        ../libosmscout/include/osmscout/util/NumberSet.h \
        ../libosmscout/include/osmscout/util/Parser.h \
        ../libosmscout/include/osmscout/util/Progress.h \
        ../libosmscout/include/osmscout/util/Projection.h \
        ../libosmscout/include/osmscout/util/Reference.h \
        ../libosmscout/include/osmscout/util/StopClock.h \
        ../libosmscout/include/osmscout/util/String.h \
        ../libosmscout/include/osmscout/util/Tiling.h \
        ../libosmscout/include/osmscout/util/Transformation.h
