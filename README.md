# CourseDesign
Copyright © 2019 icegrave0391. All rights reserved.    
*四种功能实现模块* :    
+ CNF范式求解模块     
> DPLL
+ 数独游戏生成模块
> LasVegas + 挖洞
+ 文件操作模块
+ 数独转化SAT问题
> minimal encoing + extended encoding

## DataStructure
这里`Clause`以及`Formula` 均使用单链表实现，如想参考其他版本，移步其他branch    
*branch DPLLOptimize* : `Clause`使用数组，`Formula`使用链表    
*branch DPLLOptimize3* : `Clause`使用数组，`Formula`使用链表， 同时加入`Literal Stack`以及指向`Clause`的`literal pointer array`    

### API Clause
```
enum LiteralContainStatus{
    LiteralContainStatusNotContain = 0,
    LiteralContainStatusContain,
    LiteralContainStatusContainInverse
//    LiteralContainStatusContainBoth
};

typedef enum LiteralContainStatus LiteralContainStatus;

#pragma mark - Clause struct
struct Clause{
    int literal ;
    struct Clause * next ;
}  ;
typedef struct Clause Clause;
typedef Clause * clause ;

//clause operate functions

//clause createClause(int literalNum, ClauseStatus clsStatus, int * literals) ;
int initClause(clause * cls) ;
clause createClause(int literalNum, int * literals) ;
clause deepCpyClause(clause aclause) ;
//int destoryClause(clause cls) ;
int isUnitClause (Clause cls) ;
int isEmptyClause(Clause cls) ;
LiteralContainStatus literalStatusWithClause(Clause Cls, int literal) ;
void deleteLiteral(clause * cls, int literal) ;
int findRandomLiteral(clause cls) ;
int findFirstLiteral(clause cls) ;
void addLiteral(clause * cls, int literal) ;
```
### API Formula
```
enum DeleteClauseStatus{
    DeleteClauseStatusNotFound = 0,
    DeleteClauseStatusSuccessful
};
typedef enum DeleteClauseStatus DeleteClauseStatus;
#pragma mark - structure
struct FormulaNode{
    clause clause ;
    struct FormulaNode * next ;
};
typedef struct FormulaNode * formulaList;

// Formula functions
int init(formulaList * ls) ;
int isFormulaEmpty(formulaList Ls) ;
int clauseNum(formulaList Ls) ;

int emptyClauseInFormula(formulaList Ls) ;
#pragma mark - clause operations
void addClause(formulaList * ls, clause cls) ;
void addUnitClause(formulaList * ls, clause cls) ;

DeleteClauseStatus deleteClause(formulaList * ls, clause cls) ;
clause findUnitClause(formulaList Ls) ;
clause findFirstStillClase(formulaList Ls) ;
#pragma mark - formula cpy
formulaList deepCpyFormulaList(formulaList Ls) ;
```

## DPLL
最终版本：深复制 + 递归回溯（使用深复制）,如想参考其他版本，移步其他branch    
`DPLLOptimize3` : 递归回溯 + `pop stack` undo复原状态
* 文字最终解 : `extern int * allLiteralArr`

## CNFFileManager 
``` formulaList loadCNFFileFormula(char * filePath) ; ```   
> 解析CNF文件，并返回其存储公式    

``` int exportDPLLResultFile(char * filePath, int * literalsArr, int DPLLResult, double timeinterval) ; ```
> 将公式最终解导出.res文件    
> DPLLResult对应返回值有无解， timeinterval对应clock

## SudokuTransfer
### API
```
//this method create beginning board to both constraints .sud file and .cnf file    
//数独转化SAT(生成.sud数独约束文件 以及.cnf 求解文件)
int transferConstraintToFile(int sudoku[9][9]) ;    

//should only be sudoku constraint literal (111 - 999 without number 0)    

int mapSudokuToLiteral(int sudoku) ;    
int mapLiteralToSudoku(int literal) ;    

// this method should only be used in .res file    
void transferSudokuAnswer(char * filePath) ;

#pragma mark - create sudoku & beginning board

//数独求解器
int DFSSovleSudoku(int sudokuBoard[9][9], int r[9][10], int c[9][10], int b[9][10]) ;
// n means write n random nums 填数(11+)的拉斯维加斯算法
int lasVegasCreateSudoku(int n) ;

//挖洞
void generateSudokuByDigHoles(int remains) ;
//判断是否唯一解
int uniqueSolution(int row, int line) ;
```
数独生成器(初盘) : `extern int sudokuBoard[row][col]`     
数独答案终盘 : `extern int sudokuSolution[row][col]`
