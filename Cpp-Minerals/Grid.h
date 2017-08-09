//
//  Grid.hpp
//  Minerals
//
//  Created by Michael Adaixo on 29/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <iostream>
#include <functional>
#include <queue>
#include <iterator>
#include <tuple>
#include <cmath>
#include <list>
#include <algorithm>
#include <ctime>

#include "Rect.h"
#include "Vector2.h"
#include "Texture.h"

class Math;

#define CELL_TYPES 6
#define CELL_Y_OFFSET 0
#define CELL_X_OFFSET 0
#define CELL_SPACING 0
#define CELL_SIZE 65
#define CELL_FALL_SPEED 5

enum CellColor {
    EMPTY = 0,
    WHITE,
    BLUE,
    RED,
    YELLOW,
    GREEN
};

class Grid;

struct GridCell 
{
    int IndexX;
    int IndexY;
    
    Vector2 Position;
    Vector2 Destination;
    
    bool Visited;
    bool NeedsUpdateInPosition;
    
    CellColor State;
    
    GridCell( )
    {
        IndexX = 0;
        IndexY = 0;
        
        Position = Vector2();
        Destination = Vector2();
        State = CellColor::EMPTY;
        Visited = false;
        NeedsUpdateInPosition = false;
    }
    
    GridCell( const GridCell& cell )
    {
        IndexX = cell.IndexX;
        IndexY = cell.IndexY;
        Position = cell.Position;
        Destination = cell.Destination;
        State = cell.State;
        Visited = cell.Visited;
        NeedsUpdateInPosition = cell.NeedsUpdateInPosition;
    }
    
    GridCell( int x, int y, CellColor state )
    {
        IndexX = x;
        IndexY = y;
        
        Position = Vector2( x * CELL_SIZE, y * CELL_SIZE );
        Destination = Position;
        
        Visited = false;
        NeedsUpdateInPosition = false;
        
        State = state;
    }
    
    Rect GetRect( )
    {
        return Rect( Position, CELL_SIZE, CELL_SIZE );
    }
    
    void UpdatePosition( float deltaTime )
    {
        Vector2 diff = ( Destination - Position ) * deltaTime * CELL_FALL_SPEED;
        if( diff.LengthSqr() > 0.001f )
        {
            Position += diff;
        }
        else
        {
            NeedsUpdateInPosition = false;
        }
    }
    
    void MoveTo( int x, int y )
    {
        IndexX = x;
        IndexY = y;
        Destination = Vector2( x * CELL_SIZE, y * CELL_SIZE );
        NeedsUpdateInPosition = true;
    }
    
    void PopCell( )
    {
        State = CellColor::EMPTY;
    }
};


class Grid
{
public:
    Grid( int x, int y, Vector2 position );
    ~Grid();
    
    void LoadResources( SDL_Renderer *renderer );
    void Cleanup();
    
    void GenerateGrid( );
    
    void Reset( );
    void ResetVisitedCells( );
    void MakeNewBlock( );
    void PushNewColumn( );
    
    bool CheckEndGame( );
    
    void Update( float deltaTime );
    
    void ApplyGravity( );
    
    void SwapAndUpdateGridCells( GridCell a, GridCell b );
    void SwapAndUpdateGridCells( int ax, int ay, int bx, int by );

    //    void UpdateGridCell( GridCell a );
    bool IsInBounds( GridCell a );
    bool IsInBounds( int x, int y );
    
    GridCell MakeGridCell( int x, int y );
    
    GridCell* GetLastCellEmptyBelow( GridCell a );
    
    void RenderGrid( SDL_Renderer *renderer );
    void RenderCells( SDL_Renderer *renderer );
    
    int PopCellsAt( float x, float y );
    
    void MoveColumnsToLeft( std::vector<int> columnIndexes );
    std::vector<int> FindEmptyColumns( );
    std::vector<GridCell*> FindAjdacent( int x, int y );
    void PopGridCells( std::vector<GridCell*> cells );
    
    std::vector<GridCell*> GetCellsOfColor( CellColor color );
    std::vector<GridCell*> GetNeighborsSameColor( GridCell a );
    std::vector<GridCell*> GetNeighbors( GridCell a, bool diagonal );
    
    GridCell* GetCell( int x, int y ) {
        if( m_grid != nullptr && IsInBounds(x, y) )
        {
            return &m_grid[x][y];
        }
        return nullptr;
    }
    
private:
    Vector2 m_position;
    GridCell **m_grid;
    
    std::vector<GridCell> m_newBlocks;
    
    int m_height;
    int m_width;
    
    bool m_centerGrid;
    
    Texture m_textures[CELL_TYPES];
    Texture m_textureDeadCell;
    Texture m_textureOverlay;
};


