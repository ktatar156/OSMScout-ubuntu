/*
  DumpData - a demo program for libosmscout
  Copyright (C) 2012  Tim Teulings

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <cstring>
#include <iostream>

#include <osmscout/Database.h>
#include <osmscout/DebugDatabase.h>

#include <list>
#include <map>
#include <string>
#include <vector>

/*
 * Example:
 *   src/DumpData ../TravelJinni/ -n 25293125 -w 4290108 -w 26688152 -r 531985
 */

struct Job
{
  osmscout::ObjectOSMRef  osmRef;
  osmscout::ObjectFileRef fileRef;

  Job()
  {
    // no code
  }

  Job(osmscout::OSMRefType type, osmscout::Id id)
  : osmRef(id,type)
  {
    // no code
  }

  Job(osmscout::RefType type, osmscout::FileOffset fileOffset)
  : fileRef(fileOffset,type)
  {
    // no code
  }
};

static bool ParseArguments(int argc,
                           char* argv[],
                           std::string& map,
                           std::list<osmscout::Id>& coordIds,
                           std::list<Job>& jobs)
{
  if (argc<2) {
    std::cerr << "DumpData <map directory> {-c <Id>|-n <Id>|-no <FileOffset>|-w <Id>|-wo <FileOffset>|-r <Id>|-ro <FileOffset>}" << std::endl;
    return false;
  }

  int arg=1;

  map=argv[arg];

  arg++;

  while (arg<argc) {
    if (strcmp(argv[arg],"-c")==0) {
      unsigned long id;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -c requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&id)!=1) {
        std::cerr << "Node id is not numeric!" << std::endl;
        return false;
      }

      coordIds.push_back(id);

      arg++;
    }

    //
    // OSM types (nodes, ways, relations)
    //

    else if (strcmp(argv[arg],"-n")==0) {
      unsigned long id;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -n requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&id)!=1) {
        std::cerr << "Node id is not numeric!" << std::endl;
        return false;
      }

      jobs.push_back(Job(osmscout::osmRefNode,id));

      arg++;
    }
    else if (strcmp(argv[arg],"-w")==0) {
      unsigned long id;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -w requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&id)!=1) {
        std::cerr << "Node id is not numeric!" << std::endl;
        return false;
      }

      jobs.push_back(Job(osmscout::osmRefWay,id));

      arg++;
    }
    else if (strcmp(argv[arg],"-r")==0) {
      unsigned long id;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -r requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&id)!=1) {
        std::cerr << "Relation id is not numeric!" << std::endl;
        return false;
      }

      jobs.push_back(Job(osmscout::osmRefRelation,id));

      arg++;
    }

    //
    // libosmscout types (nodes, ways, areas)
    //

    else if (strcmp(argv[arg],"-no")==0) {
      unsigned long fileOffset;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -no requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&fileOffset)!=1) {
        std::cerr << "Node id is not numeric!" << std::endl;
        return false;
      }

      jobs.push_back(Job(osmscout::refNode,fileOffset));

      arg++;
    }
    else if (strcmp(argv[arg],"-wo")==0) {
      unsigned long fileOffset;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -wo requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&fileOffset)!=1) {
        std::cerr << "Way file offset is not numeric!" << std::endl;
        return false;
      }

      jobs.push_back(Job(osmscout::refWay,fileOffset));

      arg++;
    }
    else if (strcmp(argv[arg],"-ao")==0) {
      unsigned long fileOffset;

      arg++;
      if (arg>=argc) {
        std::cerr << "Option -ro requires parameter!" << std::endl;
        return false;
      }

      if (sscanf(argv[arg],"%lu",&fileOffset)!=1) {
        std::cerr << "Relation file offset is not numeric!" << std::endl;
        return false;
      }

      jobs.push_back(Job(osmscout::refWay,fileOffset));

      arg++;
    }


    else {
      std::cerr << "Unknown parameter '" << argv[arg] << "'!" << std::endl;
      return false;
    }
  }

  return true;
}

static void DumpIndent(size_t indent)
{
  for (size_t i=1; i<=indent; i++) {
    std::cout << " ";
  }
}

static void DumpCoord(const osmscout::Point& coord)
{
  std::cout << "Coord {" << std::endl;
  std::cout << "  id: " << coord.GetId() << std::endl;
  std::cout << "  lat: " << coord.GetLat() << std::endl;
  std::cout << "  lon: " << coord.GetLon() << std::endl;
  std::cout << "}" << std::endl;
}

static void DumpNode(const osmscout::TypeConfig* typeConfig,
                     const osmscout::NodeRef node,
                     osmscout::Id id)
{
  std::cout << "Node {" << std::endl;
  std::cout << "  id: " << id << std::endl;
  std::cout << "  fileOffset: " << node->GetFileOffset() << std::endl;

  if (node->GetType()!=osmscout::typeIgnore) {
    std::cout << "  type: " << typeConfig->GetTypeInfo(node->GetType()).GetName() << std::endl;
  }

  std::cout << "  lat: " << node->GetLat() << std::endl;
  std::cout << "  lon: " << node->GetLon() << std::endl;

  if (node->HasTags()) {
    std::cout << std::endl;

    for (size_t t=0; t<node->GetTagCount(); t++) {
      std::cout << "  " << typeConfig->GetTagInfo(node->GetTagKey(t)).GetName() << ": " << node->GetTagValue(t) << std::endl;
    }
  }

  std::cout << "}" << std::endl;
}

static void DumpAreaSegmentAttributes(const osmscout::AreaAttributes& attributes,
                                      const osmscout::TypeConfig* typeConfig,
                                      size_t indent)
{
  if (attributes.GetType()!=osmscout::typeIgnore) {
    DumpIndent(indent);
    std::cout << "type: " << typeConfig->GetTypeInfo(attributes.GetType()).GetName() << std::endl;
  }

  if (!attributes.GetName().empty()) {
    DumpIndent(indent);
    std::cout << "name: " << attributes.GetName() << std::endl;
  }

  if (!attributes.GetNameAlt().empty()) {
    DumpIndent(indent);
    std::cout << "nameAlt: " << attributes.GetNameAlt() << std::endl;
  }

  if (!attributes.HasAccess()) {
    DumpIndent(indent);
    std::cout << "access: false" << std::endl;
  }

  if (!attributes.GetHouseNr().empty()) {
    DumpIndent(indent);
    std::cout << "houseNr: " << attributes.GetHouseNr() << std::endl;
  }
}

static void DumpWayAttributes(const osmscout::WayAttributes& attributes,
                              const osmscout::TypeConfig* typeConfig,
                              size_t indent)
{
  if (attributes.GetType()!=osmscout::typeIgnore) {
    DumpIndent(indent);
    std::cout << "type: " << typeConfig->GetTypeInfo(attributes.GetType()).GetName() << std::endl;
  }

  if (!attributes.GetName().empty()) {
    DumpIndent(indent);
    std::cout << "name: " << attributes.GetName() << std::endl;
  }

  if (!attributes.GetNameAlt().empty()) {
    DumpIndent(indent);
    std::cout << "nameAlt: " << attributes.GetNameAlt() << std::endl;
  }

  if (!attributes.GetRefName().empty()) {
    DumpIndent(indent);
    std::cout << "ref: " << attributes.GetRefName() << std::endl;
  }

  if (!attributes.HasAccess()) {
    DumpIndent(indent);
    std::cout << "access: false" << std::endl;
  }

  if (attributes.IsBridge()) {
    DumpIndent(indent);
    std::cout << "bridge: true" << std::endl;
  }

  if (attributes.IsTunnel()) {
    DumpIndent(indent);
    std::cout << "tunnel: true" << std::endl;
  }

  if (attributes.IsOneway()) {
    DumpIndent(indent);
    std::cout << "oneway: true" << std::endl;
  }

  if (attributes.IsRoundabout()) {
    DumpIndent(indent);
    std::cout << "roundabout: true" << std::endl;
  }

  if (attributes.GetWidth()!=0) {
    DumpIndent(indent);
    std::cout << "width: " << (size_t)attributes.GetWidth() << std::endl;
  }

  if (attributes.GetLayer()!=0) {
    DumpIndent(indent);
    std::cout << "layer: " << (size_t)attributes.GetLayer() << std::endl;
  }

  if (attributes.GetMaxSpeed()!=0) {
    DumpIndent(indent);
    std::cout << "maxSpeed: " << (size_t)attributes.GetMaxSpeed() << std::endl;
  }

  DumpIndent(indent);
  std::cout << "grade: " << (size_t)attributes.GetGrade() << std::endl;
}

static void DumpWay(const osmscout::TypeConfig* typeConfig,
                    const osmscout::WayRef way,
                    osmscout::Id id)
{
  std::cout << "Way {" << std::endl;

  std::cout << "  id: " << id << std::endl;
  std::cout << "  fileOffset: " << way->GetFileOffset() << std::endl;

  DumpWayAttributes(way->GetAttributes(),
                    typeConfig,
                    2);

  if (way->HasTags()) {
    std::cout << std::endl;

    for (size_t t=0; t<way->GetTagCount(); t++) {
      std::cout << "  " << typeConfig->GetTagInfo(way->GetTagKey(t)).GetName() << ": " << way->GetTagValue(t) << std::endl;
    }
  }

  if (!way->nodes.empty()) {
    std::cout << std::endl;

    for (size_t n=0; n<way->nodes.size(); n++) {
      std::cout << "  node[" << n << "] {";

      if (way->ids[n]!=0) {
        std::cout << " id: " << way->ids[n];
      }

      std::cout << " lat: " << way->nodes[n].GetLat() << " lon: "<< way->nodes[n].GetLon() << " }" << std::endl;
    }
  }

  std::cout << "}" << std::endl;
}

static void DumpArea(const osmscout::TypeConfig* typeConfig,
                     const osmscout::AreaRef area,
                     osmscout::Id id)
{
  std::cout << "Area {" << std::endl;

  std::cout << "  id: " << id << std::endl;
  std::cout << "  fileOffset: " << area->GetFileOffset() << std::endl;

  DumpAreaSegmentAttributes(area->GetAttributes(),
                            typeConfig,
                            2);

  for (size_t r=0; r<area->rings.size(); r++) {
    std::cout << std::endl;
    std::cout << "  role[" << r << "] {" << std::endl;

    std::cout << "    ring: " << (size_t)area->rings[r].ring << std::endl;

    DumpAreaSegmentAttributes(area->rings[r].GetAttributes(),
                              typeConfig,
                              4);

    std::cout << "  }" << std::endl;
  }

  if (area->HasTags()) {
    std::cout << std::endl;

    for (size_t t=0; t<area->GetTagCount(); t++) {
      std::cout << "  " << typeConfig->GetTagInfo(area->GetTagKey(t)).GetName() << ": " << area->GetTagValue(t) << std::endl;
    }
  }

  std::cout << "}" << std::endl;
}

int main(int argc, char* argv[])
{
  std::string                    map;
  std::list<Job>                 jobs;

  std::list<osmscout::Id>        coordIds;

  if (!ParseArguments(argc,
                      argv,
                      map,
                      coordIds,
                      jobs)) {
    return 1;
  }

  osmscout::DatabaseParameter      databaseParameter;
  osmscout::Database               database(databaseParameter);
  osmscout::DebugDatabaseParameter debugDatabaseParameter;
  osmscout::DebugDatabase          debugDatabase(debugDatabaseParameter);

  if (!database.Open(map.c_str())) {
    std::cerr << "Cannot open database" << std::endl;
  }

  if (!debugDatabase.Open(map.c_str())) {
    std::cerr << "Cannot open debug database" << std::endl;
  }

  // OSM ids
  std::set<osmscout::ObjectOSMRef>  osmRefs;
  std::set<osmscout::ObjectFileRef> fileRefs;

  for (std::list<Job>::const_iterator job=jobs.begin();
       job!=jobs.end();
       ++job) {
    switch (job->osmRef.GetType()) {
    case osmscout::osmRefNone:
      break;
    case osmscout::osmRefNode:
    case osmscout::osmRefWay:
    case osmscout::osmRefRelation:
      osmRefs.insert(job->osmRef);
      break;
    }

    switch (job->fileRef.GetType()) {
    case osmscout::refNone:
      break;
    case osmscout::refNode:
    case osmscout::refArea:
    case osmscout::refWay:
      fileRefs.insert(job->fileRef);
      break;
    }
  }

  std::map<osmscout::ObjectOSMRef,osmscout::ObjectFileRef> idFileOffsetMap;
  std::map<osmscout::ObjectFileRef,osmscout::ObjectOSMRef> fileOffsetIdMap;

  if (!osmRefs.empty() ||
      !fileRefs.empty()) {
    if (!debugDatabase.ResolveReferences(osmRefs,
                                         fileRefs,
                                         idFileOffsetMap,
                                         fileOffsetIdMap)) {
      std::cerr << "Error while resolving node ids and file offsets" << std::endl;
    }
  }

  std::vector<osmscout::Point>   coords;
  std::vector<osmscout::NodeRef> nodes;
  std::vector<osmscout::AreaRef> areas;
  std::vector<osmscout::WayRef>  ways;

  if (!coordIds.empty()) {
    std::vector<osmscout::Id> ids(coordIds.begin(),coordIds.end());

    if (!debugDatabase.GetCoords(ids,
                                 coords)) {
      std::cerr << "Error whole loading coords by id" << std::endl;
    }
  }

  if (!fileOffsetIdMap.empty()) {
    std::list<osmscout::FileOffset> offsets;

    for (std::map<osmscout::ObjectFileRef,osmscout::ObjectOSMRef>::const_iterator entry=fileOffsetIdMap.begin();
         entry!=fileOffsetIdMap.end();
         ++entry) {
      if (entry->first.GetType()==osmscout::refNode) {
        offsets.push_back(entry->first.GetFileOffset());
      }
    }

    if (!database.GetNodesByOffset(offsets,
                                   nodes)) {
      std::cerr << "Error whole loading nodes by offset" << std::endl;
    }
  }

  if (!fileOffsetIdMap.empty()) {
    std::list<osmscout::FileOffset> offsets;

    for (std::map<osmscout::ObjectFileRef,osmscout::ObjectOSMRef>::const_iterator entry=fileOffsetIdMap.begin();
         entry!=fileOffsetIdMap.end();
         ++entry) {
      if (entry->first.GetType()==osmscout::refArea) {
        offsets.push_back(entry->first.GetFileOffset());
      }
    }

    if (!database.GetAreasByOffset(offsets,
                                   areas)) {
      std::cerr << "Error whole loading areas by offset" << std::endl;
    }
  }

  if (!fileOffsetIdMap.empty()) {
    std::list<osmscout::FileOffset> offsets;

    for (std::map<osmscout::ObjectFileRef,osmscout::ObjectOSMRef>::const_iterator entry=fileOffsetIdMap.begin();
         entry!=fileOffsetIdMap.end();
         ++entry) {
      if (entry->first.GetType()==osmscout::refWay) {
        offsets.push_back(entry->first.GetFileOffset());
      }
    }

    if (!database.GetWaysByOffset(offsets,
                                  ways)) {
      std::cerr << "Error whole loading ways by offset" << std::endl;
    }
  }

  for (std::list<osmscout::Id>::const_iterator id=coordIds.begin();
       id!=coordIds.end();
       ++id) {
    bool found=false;

    for (size_t i=0; i<coords.size(); i++) {
      if (coords[i].GetId()==*id) {
        if (id!=coordIds.begin()) {
          std::cout << std::endl;
        }

        DumpCoord(coords[i]);
        found=true;
        break;
      }
    }

    if (!found) {
        std::cerr << "Cannot find coord with id " << *id << std::endl;
    }
  }

  for (std::list<Job>::const_iterator job=jobs.begin();
       job!=jobs.end();
       ++job) {
    if (job!=jobs.begin() ||
        !coordIds.empty()) {
      std::cout << std::endl;
    }

    if (job->osmRef.GetType()!=osmscout::osmRefNone) {
      std::map<osmscout::ObjectOSMRef,osmscout::ObjectFileRef>::const_iterator reference=idFileOffsetMap.find(job->osmRef);

      if (reference==idFileOffsetMap.end()) {
        std::cerr << "Cannot find '" << job->osmRef.GetTypeName() << "' with id " << job->osmRef.GetId() << std::endl;
        continue;
      }

      switch (reference->second.GetType()) {
      case osmscout::refNone:
        break;
      case osmscout::refNode:
        for (size_t i=0; i<nodes.size(); i++) {
          if (reference->second.GetFileOffset()==nodes[i]->GetFileOffset()) {
            DumpNode(debugDatabase.GetTypeConfig(),nodes[i],reference->first.GetId());
            break;
          }
        }
        break;
      case osmscout::refArea:
        for (size_t i=0; i<areas.size(); i++) {
          if (reference->second.GetFileOffset()==areas[i]->GetFileOffset()) {
            DumpArea(debugDatabase.GetTypeConfig(),areas[i],reference->first.GetId());
            break;
          }
        }
        break;
      case osmscout::refWay:
        for (size_t i=0; i<ways.size(); i++) {
          if (reference->second.GetFileOffset()==ways[i]->GetFileOffset()) {
            DumpWay(debugDatabase.GetTypeConfig(),ways[i],reference->first.GetId());
            break;
          }
        }
        break;
      }
    }
    else if (job->fileRef.GetType()!=osmscout::refNone) {
      std::map<osmscout::ObjectFileRef,osmscout::ObjectOSMRef>::const_iterator reference=fileOffsetIdMap.find(job->fileRef);

      if (reference==fileOffsetIdMap.end()) {
        std::cerr << "Cannot find '" << job->fileRef.GetTypeName() << "' with offset " << job->fileRef.GetFileOffset() << std::endl;
        continue;
      }

      switch (reference->first.GetType()) {
      case osmscout::refNone:
        break;
      case osmscout::refNode:
        for (size_t i=0; i<nodes.size(); i++) {
          if (reference->first.GetFileOffset()==nodes[i]->GetFileOffset()) {
            DumpNode(debugDatabase.GetTypeConfig(),nodes[i],reference->second.GetId());
            break;
          }
        }
        break;
      case osmscout::refArea:
        for (size_t i=0; i<areas.size(); i++) {
          if (reference->first.GetFileOffset()==areas[i]->GetFileOffset()) {
            DumpArea(debugDatabase.GetTypeConfig(),areas[i],reference->second.GetId());
            break;
          }
        }
        break;
      case osmscout::refWay:
        for (size_t i=0; i<ways.size(); i++) {
          if (reference->first.GetFileOffset()==ways[i]->GetFileOffset()) {
            DumpWay(debugDatabase.GetTypeConfig(),ways[i],reference->second.GetId());
            break;
          }
        }
        break;
      }
    }
  }

  database.Close();

  debugDatabase.Close();

  return 0;
}
