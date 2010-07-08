#ifndef OSMSCOUT_MAP_MAPPAINTERQT_H
#define OSMSCOUT_MAP_MAPPAINTERQT_H

/*
  This source is part of the libosmscout-map library
  Copyright (C) 2010  Tim Teulings

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <qt4/QtGui/QPainter>

#include <osmscout/Private/MapImportExport.h>

#include <osmscout/MapPainter.h>

namespace osmscout {

  class OSMSCOUT_MAP_API MapPainterQt : public MapPainter
  {
    QPainter *painter;
    
    std::map<size_t,QFont*> fonts; //! Cached fonts
    
  private:    
    QFont* GetFont(const MapParameter& parameter,
                   double fontSize);
  
  protected:
    bool HasIcon(const StyleConfig& styleConfig,
                         IconStyle& style);
    
    void ClearArea(const StyleConfig& styleConfig,
                           const Projection& projection,
                           const MapParameter& parameter,
                           const MapData& data);
                                                      
    void DrawLabel(const Projection& projection,
                   const MapParameter& parameter,
                   const LabelStyle& style,
                   const std::string& text,
                   double x, double y);

    void DrawContourLabel(const Projection& projection,
                          const MapParameter& parameter,
                          const LabelStyle& style,
                          const std::string& text,
                          const std::vector<Point>& nodes);
                           
    void DrawIcon(const IconStyle* style,
                          double x, double y);
                          
    void DrawSymbol(const SymbolStyle* style,
                            double x, double y);
                          
    void DrawPath(LineStyle::Style style,
                  const Projection& projection,
                  double r,
                  double g,
                  double b,
                  double a,
                  double width,
                  const std::vector<Point>& nodes);
                                           
    void DrawWayOutline(const StyleConfig& styleConfig,
                        const Projection& projection,
                        const MapParameter& parameter,
                        TypeId type,
                        const SegmentAttributes& attributes,
                        const std::vector<Point>& nodes);

    void DrawArea(const StyleConfig& styleConfig,
                  const Projection& projection,
                  TypeId type,
                  int layer,
                  const SegmentAttributes& attributes,
                  const std::vector<Point>& nodes);  
                          
    void SetPen(const LineStyle* style, double lineWidth);                      
    void SetBrush();
    void SetBrush(const FillStyle* fillStyle);
    
  public:
    MapPainterQt();
    ~MapPainterQt();


    bool DrawMap(const StyleConfig& styleConfig,
                 const Projection& projection,
                 const MapParameter& parameter,
                 const MapData& data,
                 QPainter* painter);
  };
}

#endif