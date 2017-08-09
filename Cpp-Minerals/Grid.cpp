//
//  Grid.cpp
//  Minerals
//
//  Created by Michael Adaixo on 29/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "Grid.h"

Grid::Grid( int x, int y, Vector2 position ) : m_width(x), m_height(y), m_centerGrid(true), m_position(position)
{
    srand(time(NULL));
    
    m_grid = new GridCell*[m_width];
    for( int i = 0; i < m_width; i++ )
    {
        m_grid[i] = new GridCell[m_height];
    }
}

Grid::~Grid( )
{
    for( int i = 0; i < m_width; i++ )
    {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}

void Grid::LoadResources( SDL_Renderer *renderer )
{
    m_textures[CellColor::EMPTY].LoadFromFile(renderer, "Data/empty_slot.png");
    m_textures[CellColor::WHITE].LoadFromFile(renderer, "Data/white.png");
    m_textures[CellColor::BLUE].LoadFromFile(renderer, "Data/blue.png");
    m_textures[CellColor::RED].LoadFromFile(renderer, "Data/red.png");
    m_textures[CellColor::YELLOW].LoadFromFile(renderer, "Data/orange.png");
    m_textures[CellColor::GREEN].LoadFromFile(renderer, "Data/green.png");
    
    m_textureDeadCell.LoadFromFile(renderer, "Data/danger.png");
    m_textureOverlay.LoadFromFile(renderer, "Data/overlay.png");
}

void Grid::Cleanup( )
{
    for( int i = 0; i < CELL_TYPES; i++ )
        m_textures->Clear();
}

void Grid::GenerateGrid()
{
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            m_grid[x][y] = MakeGridCell(x, y);
        }
    }
}

void Grid::Reset( )
{
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            m_grid[x][y] = GridCell();
        }
    }
    
    m_newBlocks.clear();
}

void Grid::ResetVisitedCells( )
{
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            m_grid[x][y].Visited = false;
        }
    }
}

GridCell Grid::MakeGridCell( int x, int y )
{
    int next = 1;
    do {
        next = (int) floor( Math::Random01() * CELL_TYPES) + 0.5;
    } while( next == 0 );
    
    if( x > m_width - 5 ) {
        next = CellColor::EMPTY;
    }
    
    return GridCell(x, y, (CellColor) next);
}

void Grid::MakeNewBlock()
{
    std::cout << "Make new block.. push others up" << std::endl;
    if( m_newBlocks.size() == 8 )
    {
        PushNewColumn();
    }
    else
    {
        GridCell block = MakeGridCell(-1, m_height);
        m_newBlocks.push_back(block);
        
        for( int i = 0; i < m_newBlocks.size(); i++ )
        {
            m_newBlocks[i].MoveTo(m_newBlocks[i].IndexX, m_newBlocks[i].IndexY - 1);
        }
    }
}

void Grid::PushNewColumn()
{
    std::cout << "Pushing block column" << std::endl;
    
    for( int x = m_width - 1; x >= 0; x-- )
    {
        for( int y = 0; y < m_height; y++ )
        {
            // To the right people!! nothing to see here.. move along!.
            if( IsInBounds(x - 1, y) )
            {
                SwapAndUpdateGridCells( m_grid[x][y], m_grid[x-1][y] );
            }
        }
    }
    
    for( int i = 0; i < m_newBlocks.size(); i++ )
    {
        GridCell cell = m_newBlocks[i];
        m_grid[0][cell.IndexY] = cell;
        m_grid[0][cell.IndexY].MoveTo(0, cell.IndexY);
    }
    
    m_newBlocks.clear();
}

// if there is at least 1 adjacent to another one
// then its no complete. break and carry on.
bool Grid::CheckEndGame( )
{
    for( int y = 0; y < m_height; y++ )
    {
        if( m_grid[m_width-1][y].State != CellColor::EMPTY )
        {
            return true;
        }
    }
    return false;
//    for( int x = 0; x < m_width; x++ )
//    {
//        for( int y = 0; y < m_height; y++ )
//        {
//            GridCell* cell = &m_grid[x][y];
//            std::vector<GridCell*> adjacents = FindAjdacent(cell->IndexX, cell->IndexY);
//            if( adjacents.size() > 1 )
//                return false;
//        }
//    }
//    return true;
}

void Grid::Update( float deltaTime )
{
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            if( !m_grid[x][y].NeedsUpdateInPosition )
                continue;
            
            m_grid[x][y].UpdatePosition( deltaTime );
        }
    }
    
    for( int i = 0; i < m_newBlocks.size(); i++ )
    {
        if( m_newBlocks[i].NeedsUpdateInPosition )
            m_newBlocks[i].UpdatePosition(deltaTime);
    }
}

void Grid::ApplyGravity()
{
    std::vector< std::tuple<GridCell*, GridCell*> > blocksToSwap;

    // 1 - check all blocks that have empty space below them.
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            if( m_grid[x][y].State == CellColor::EMPTY /* || m_grid[x][y].NeedsUpdateInPosition */ )
            {
                continue;
            }
    
            // for each column width (x), check all heights. so higher indexes ( which is below )
            // if there is adjacent empty cell. continue, and save the second tupple.
            // if there is no empty, continue to next.
            GridCell *tupleA = GetCell(x, y);
            if( tupleA != NULL )
            {
                GridCell *lastEmptyBellow = GetLastCellEmptyBelow(*tupleA);
                if( lastEmptyBellow != NULL )
                {
                    blocksToSwap.push_back( std::make_tuple(tupleA, lastEmptyBellow) );
                }
            }
        }
    }
    
    if( blocksToSwap.size() < 1 ) return;
    
    std::cout << "blocks to fall " << blocksToSwap.size() << std::endl;
    
    // 2 - loop those and make them fall untill they find a block.
    for( int i = 0; i < blocksToSwap.size(); i++ )
    {
        auto tuple = blocksToSwap[i];
        GridCell* a = std::get<0>(tuple);
        GridCell* b = std::get<1>(tuple);
        
        SwapAndUpdateGridCells(*a, *b);
    }
    
    // 3 - rinse and repeat untill there are no more to fall :D
    ApplyGravity();
}

void Grid::SwapAndUpdateGridCells( GridCell a, GridCell b )
{
    if( IsInBounds(a) && IsInBounds(b) )
    {
        // since now I am holding references to the gridcells.
        // they are referenced from the board.
        // so any changes should be fiiiiiine.. now.. and
        // automatically applied to the board.
        // so if a(0, 1) -> b(0, 3)
        // I have to move a to b.
        
        GridCell tmp = a;
        m_grid[a.IndexX][a.IndexY] = b;
        m_grid[b.IndexX][b.IndexY] = tmp;
        
        m_grid[a.IndexX][a.IndexY].MoveTo(a.IndexX, a.IndexY);
        m_grid[b.IndexX][b.IndexY].MoveTo(b.IndexX, b.IndexY);
    }
}

void Grid::SwapAndUpdateGridCells( int ax, int ay, int bx, int by )
{
    if( IsInBounds(ax, ay) && IsInBounds(bx, by) )
        SwapAndUpdateGridCells( m_grid[ax][ay], m_grid[bx][by] );
    
//    if( IsInBounds(ax, ay) && IsInBounds(bx, by) )
//    {
//        GridCell tmp = m_grid[ax][ay];
//        m_grid[ax][ay] = m_grid[bx][by];
//        m_grid[bx][by] = tmp;
//        
//        m_grid[ax][ay].MoveTo(m_grid[ax][ay].IndexX, m_grid[ax][ay].IndexY);
//        m_grid[bx][by].MoveTo(m_grid[bx][by].IndexX, m_grid[bx][by].IndexY);
//    }
}

// calling these two too many times I think... so inlining them.. just in case.
inline bool Grid::IsInBounds( GridCell a )
{
    return IsInBounds( a.IndexX, a.IndexY );
}

inline bool Grid::IsInBounds( int x, int y )
{
    return ( x >= 0 && y >= 0 && x < m_width && y < m_height );
}

GridCell* Grid::GetLastCellEmptyBelow( GridCell a )
{
    GridCell *lastAdjacentEmtpy = NULL;
    int x = a.IndexX;
    int starty = a.IndexY + 1;
    for( int y = starty; y < m_height; y++ )
    {
        if( m_grid[x][y].State != CellColor::EMPTY )
            break;

        lastAdjacentEmtpy = &m_grid[x][y];
    }
    return lastAdjacentEmtpy;
}


void Grid::RenderGrid( SDL_Renderer *renderer )
{
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            Vector2 position;
            position.x = m_position.x + x * CELL_SIZE + x * CELL_SPACING;
            position.y = m_position.y + y * CELL_SIZE + y * CELL_SPACING;
            
            if( x == m_width - 1 )
            {
                m_textureDeadCell.Render(renderer, position);
            }
            else
            {
                m_textures[CellColor::EMPTY].Render(renderer, position);
            }
        }
    }
    
    for( int i = 0; i < m_newBlocks.size(); i++ )
    {
        Vector2 position = m_position + m_newBlocks[i].Position + Vector2( -CELL_SPACING, m_newBlocks[i].IndexY * CELL_SPACING );
        m_textures[m_newBlocks[i].State].Render(renderer, position);
    }
}

void Grid::RenderCells( SDL_Renderer *renderer )
{
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            GridCell cell = m_grid[x][y];
            if( cell.State == CellColor::EMPTY )
                continue;
            
            Vector2 position = m_position + cell.Position + Vector2( x * CELL_SPACING, y * CELL_SPACING );
            
            m_textures[cell.State].Render(renderer, position);
        }
    }
}

int Grid::PopCellsAt( float x, float y )
{
    int poppedCellCount = 0;
    
    int indexX = ( x - m_position.x ) / ( CELL_SIZE );
    int indexY = ( y - m_position.y ) / ( CELL_SIZE );

    std::cout << "x: " << indexX << ", y: " << indexY << std::endl;
    
    // Is in map range.
    if( IsInBounds(indexX, indexY) )
    {
        // cell rect, plus grid initial position
        Rect closerCell = Rect( Vector2( (indexX * CELL_SIZE) + m_position.x, (indexY * CELL_SIZE) + m_position.y ), CELL_SIZE, CELL_SIZE);
        if( closerCell.Contains(x, y) )
        {
            // we have a successfull cell click!
            GridCell* clickedCell = GetCell(indexX, indexY);
            if( clickedCell->State == CellColor::EMPTY )
                return poppedCellCount;
            
            std::vector<GridCell*> adjacentCells = FindAjdacent(indexX, indexY);

            std::cout << "There are " << adjacentCells.size() << " adjacent cells with the same state" << std::endl;

            if( adjacentCells.size() > 1 )
            {
                poppedCellCount = (int) adjacentCells.size();
                
                PopGridCells( adjacentCells );
                
                ApplyGravity();
                
                std::vector<int> emptyColIndexes = FindEmptyColumns();
                if( emptyColIndexes.size() > 0 )
                    MoveColumnsToLeft( emptyColIndexes );
            }
        }
    }
    
    return poppedCellCount;
}

void Grid::MoveColumnsToLeft( std::vector<int> columnIndexes )
{
    // I know about unsigned long, but this will cause i >= 0 to be always true
    // therefore, not stoping the condition and making an BAD_ACCESS Exception.
    // edit: changed from int to long.. removes the warning.
    for( long i = columnIndexes.size() - 1; i >= 0; i-- )
    {
        int currentColumn = columnIndexes[i];
        for( int x = currentColumn; x < m_width; x++ )
        {
            for( int y = 0; y < m_height; y++ )
            {
                if( IsInBounds(x + 1, y) )
                {
                    SwapAndUpdateGridCells( m_grid[x][y], m_grid[x+1][y] );
                }
            }
        }
    }
}



std::vector<int> Grid::FindEmptyColumns()
{
    std::vector<int> emptyColumnsIndexes;
    for( int x = 0; x < m_width; x++ )
    {
        GridCell *lastCellBelow = GetLastCellEmptyBelow( m_grid[x][0] );
        if( lastCellBelow != NULL && lastCellBelow->IndexY == m_height - 1)
        {
            // we have a winner!
            emptyColumnsIndexes.push_back(x);
        }
    }
    return emptyColumnsIndexes;
}

// Woo Hoo!! Algorithms!!
// I could backtrack.. but.. don't need a path, just list of cells.
std::vector<GridCell*> Grid::FindAjdacent( int x, int y )
{
    std::vector<GridCell*> totalCells;
    std::queue<GridCell*> visited;
    
    ResetVisitedCells();
    
    if( !IsInBounds(x, y) || m_grid[x][y].State == CellColor::EMPTY ) // dont you go clicking empty spaces... duuuuude.. :D
        return totalCells;

    GridCell *cell = &m_grid[x][y];
    cell->Visited = true;
    
    visited.push(cell);
    
    while( visited.size() > 0 )
    {
        GridCell* currentCell = visited.front();
        
        visited.pop();
        
        totalCells.push_back(currentCell);
        
        std::vector<GridCell*> partial = GetNeighborsSameColor( *currentCell );
    
        for( int i = 0; i < partial.size(); i++ )
        {
            GridCell *neighbor = partial[i];
            if( !neighbor->Visited )
            {
                neighbor->Visited = true;
                visited.push( neighbor );
            }
        }
    }
    
    return totalCells;
}

void Grid::PopGridCells( std::vector<GridCell *> cells )
{
    for( int i = 0; i < cells.size(); i++ )
    {
        GridCell* cell = cells[i];
        cell->PopCell();
    }
}

std::vector<GridCell*> Grid::GetCellsOfColor( CellColor color )
{
    std::vector<GridCell*> result;
    for( int x = 0; x < m_width; x++ )
    {
        for( int y = 0; y < m_height; y++ )
        {
            if( m_grid[x][y].State == color )
                result.push_back( &m_grid[x][y] );
        }
    }
    return result;
}

std::vector<GridCell*> Grid::GetNeighborsSameColor( GridCell a )
{
    std::vector<GridCell*> result;
    
    // only 4 directional neighbors
    if( IsInBounds(a.IndexX - 1, a.IndexY) && m_grid[a.IndexX - 1][a.IndexY].State == a.State )
        result.push_back(&m_grid[a.IndexX - 1][a.IndexY]);
    
    if( IsInBounds(a.IndexX + 1, a.IndexY) && m_grid[a.IndexX + 1][a.IndexY].State == a.State )
        result.push_back(&m_grid[a.IndexX + 1][a.IndexY]);
    
    if( IsInBounds(a.IndexX, a.IndexY - 1) && m_grid[a.IndexX][a.IndexY - 1].State == a.State )
        result.push_back(&m_grid[a.IndexX][a.IndexY - 1]);
    
    if( IsInBounds(a.IndexX, a.IndexY + 1) && m_grid[a.IndexX][a.IndexY + 1].State == a.State )
        result.push_back(&m_grid[a.IndexX][a.IndexY + 1]);
        
    return result;
}

std::vector<GridCell*> Grid::GetNeighbors( GridCell a, bool diagonal )
{
    std::vector<GridCell*> result;
    // this works with diagonal neighbors.
    if( diagonal )
    {
        for( int x = a.IndexX - 1; x <= a.IndexX + 1; x++ )
        {
            for( int y = a.IndexY - 1; y <= a.IndexY + 1; y++ )
            {
                if( x == a.IndexX && y == a.IndexY )
                    continue; // because this is GridCell a.
    
                if( IsInBounds(x, y) && m_grid[x][y].State == a.State )
                {
                    result.push_back( &m_grid[x][y] );
                }
            }
        }
    }
    else
    {
        if( IsInBounds(a.IndexX - 1, a.IndexY) )
            result.push_back( &m_grid[a.IndexX - 1][a.IndexY] );
        
        if( IsInBounds(a.IndexX + 1, a.IndexY) )
            result.push_back( &m_grid[a.IndexX + 1][a.IndexY] );
        
        if( IsInBounds(a.IndexX, a.IndexY - 1) )
            result.push_back( &m_grid[a.IndexX][a.IndexY - 1] );
        
        if( IsInBounds(a.IndexX, a.IndexY + 1) )
            result.push_back( &m_grid[a.IndexX][a.IndexY + 1] );

    }
    return result;
}





