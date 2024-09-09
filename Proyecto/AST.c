#include "AST.h"
#include "symbol.h"
#include <stdbool.h>

struct AST* createTree(Tsymbol* symbol, struct AST *l, struct AST *r) {
    AST *arbol = (AST *)malloc(sizeof(AST));
    arbol->symbol = symbol;
    arbol->left = l;
    arbol->right = r;
    return arbol;
}

void showTree(AST* tree) {
    if (tree != NULL) {
        printf("< %s >",(tree->symbol)->varname);
        if((tree->left) != NULL){
            printf("(LEFT:");
            showTree(tree->left);
            printf(")");
        }else {
            printf("Ø");
        }
        if((tree->right) != NULL){
            printf("(RHIGT:");
            showTree(tree->right);
            printf(")");
        }else {
            printf("Ø ");
        }
    }
}

void showTreeDot(AST* tree,FILE* file) {
    if (tree == NULL) return;
    if(tree->left && tree->right ) {
        fprintf(file, "\"%d|  %s\" -> \"%d|  %s\", \"%d|  %s\";\n",(tree->symbol)->id,(tree->symbol)->varname,((tree->left)->symbol)->id, ((tree->left)->symbol)->varname,((tree->right)->symbol)->id,((tree->right)->symbol)->varname);
        showTreeDot(tree->left, file);
        showTreeDot(tree->right, file);
    }else {
        if (tree->left) {
        fprintf(file, "\"%d|  %s\" -> \"%d|  %s\" ;\n",(tree->symbol)->id,(tree->symbol)->varname,((tree->left)->symbol)->id, ((tree->left)->symbol)->varname);
        showTreeDot(tree->left, file);
        }
        if (tree->right) {
        fprintf(file, "\"%d|  %s\" -> \"%d|  %s\" ;\n",(tree->symbol)->id,(tree->symbol)->varname,((tree->right)->symbol)->id, ((tree->right)->symbol)->varname);
        showTreeDot(tree->right, file);
        }
    }

}

void printDot(AST* tree, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s\n", filename);
        return;
    }
    fprintf(file, "digraph{\n\n");
    fprintf(file, "rankdir=TB;\n\n");
    fprintf(file, "node[shape=box];\n");
    showTreeDot(tree, file);
    fprintf(file, "}\n");
    fclose(file);
}


void createTable(AST* ar) {
    if ((ar->symbol)->type == VARBOOL || (ar->symbol)->type == VARINT )  {
        Install(ar->symbol);
    }
    if (ar->left != NULL) {
        createTable(ar->left);
    }
    if (ar->right != NULL) {
        createTable(ar->right);
    }
}

bool err = false;

void typeError(AST* ar) {
    if (ar->right != NULL && ar->left != NULL) {
        enum TYPES tipoActual = (ar->symbol)->type;
        if (tipoActual == ASIG) {
            errorAsig(ar);
        }else if(tipoActual == SUMA || tipoActual == RESTA || tipoActual == PROD || tipoActual == EOR || tipoActual == EAND || tipoActual == ENOT) {
            errorOpera(ar, tipoActual);
        } 
    }
    if (ar->left != NULL) {
        typeError(ar->left);
    }
    if (ar->right != NULL) {
        typeError(ar->right);
    }    
}

void errorAsig(AST *ar){
    Tsymbol* auxDer = Lookup(((ar->right)->symbol)->varname);
    Tsymbol* auxIzq = Lookup(((ar->left)->symbol)->varname);

    enum TYPES tipoDer = ((ar->right)->symbol)->type;
    enum TYPES tipoIzq = ((ar->left)->symbol)->type;

    bool errorIntDer = (tipoDer != SUMA && tipoDer != RESTA && tipoDer != PROD && tipoDer != CONSINT);
    bool errorBoolDer = (tipoDer != EOR && tipoDer != EAND && tipoDer != ENOT && tipoDer != CONSBOOL);
    
    if(auxIzq == NULL && tipoIzq == EID) {
        printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
        err = true;
    } else if(auxIzq != NULL && auxDer != NULL && auxIzq->type != auxDer->type) {
        printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line);
        err = true;
    } else if(auxIzq != NULL && auxDer == NULL) {
        if (tipoDer == EID){
            printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
            err = true;
        } else if(auxIzq->type == VARINT && errorIntDer) {
            printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
            err = true;
        } else if(auxIzq->type == VARBOOL && errorBoolDer) {
            printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
            err = true;
        }
    }

}

void errorOpera(AST *ar, enum TYPES type){

    Tsymbol* auxDer = Lookup(((ar->right)->symbol)->varname);
    Tsymbol* auxIzq = Lookup(((ar->left)->symbol)->varname);

    enum TYPES tipoDer = ((ar->right)->symbol)->type;
    enum TYPES tipoIzq = ((ar->left)->symbol)->type;

    bool errorIntDer = (tipoDer != SUMA && tipoDer != RESTA && tipoDer != PROD && tipoDer != CONSINT);
    bool errorIzq = (tipoIzq != SUMA && tipoIzq != RESTA && tipoIzq != PROD && tipoIzq != CONSINT);
    
    
    if(type == SUMA || type == RESTA || type == PROD) {
        if(auxIzq != NULL && auxDer != NULL){
            if(auxIzq->type != VARINT || auxDer->type != VARINT) {
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line);
                err = true;
            }
        } else if(auxIzq != NULL && auxDer == NULL) { 
            if (tipoDer == EID){
                printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
                err = true;
            } else if(auxIzq->type != VARINT || errorIntDer) {
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
                err = true;
            }
        } else if(auxIzq == NULL && auxDer != NULL) {
            if (tipoIzq == EID) {
                printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
                err = true;
            } else if(auxDer->type != VARINT || errorIzq) {
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
                err = true;  
            }
        } else  if(auxIzq == NULL && auxDer == NULL){ 
            if (tipoIzq == EID || tipoDer == EID){
                printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
                err = true;
            } else if(errorIntDer || errorIzq){
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
                err = true;
            }
        }
    } else {
        
        bool errorBoolDer = (tipoDer != EOR && tipoDer != EAND && tipoDer != ENOT && tipoDer != CONSBOOL);
        bool errorBoolIzq = (tipoIzq != EOR && tipoIzq != EAND && tipoIzq != ENOT && tipoIzq != CONSBOOL);
        
        if(auxIzq != NULL && auxDer != NULL){
            if(auxIzq->type != VARBOOL || auxDer->type != VARBOOL){
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line);
                err = true;
            }
        } else if(auxIzq != NULL && auxDer == NULL) {
            if (tipoDer == EID) {
                printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
                err = true;
            } else if(auxIzq->type != VARBOOL || errorBoolDer) {
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
                err = true;
            }
        } else if(auxIzq == NULL && auxDer != NULL){
            if (tipoIzq == EID){
                printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
                err = true;
            } else if(auxDer->type != VARBOOL || errorBoolIzq){
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
                err = true;
            }
        } else if(auxIzq == NULL && auxDer == NULL){ 
            if (tipoIzq == EID || tipoDer == EID){
                printf("\033[33mVariable no declarada \033[0m, linea de error: %d\n", ((ar->left)->symbol)->line); 
                err = true;
            } else if(errorBoolIzq|| errorBoolDer){
                printf("\033[31mError de tipo \033[0m, linea de error: %d\n", ((ar->right)->symbol)->line);
                err = true;
            }
        }
    }
}

void evaluate(AST* ar) {
    if (ar->right != NULL && ar->left != NULL) {
        if (ar->left != NULL) {
            evaluate(ar->left);
        }
        if (ar->right != NULL) {
            evaluate(ar->right);
        }    
        enum TYPES tipoActual = (ar->symbol)->type;
        struct Tsymbol* auxDer = Lookup(((ar->right)->symbol)->varname);
        struct Tsymbol* auxIzq = Lookup(((ar->left)->symbol)->varname);

        if(tipoActual == ERETURN) {
            printf("%d \n", ((ar->left)->symbol)->value);
        }
        if (tipoActual == ASIG) {
            setValue(auxIzq, (ar->right)->symbol->value);
        }

        if (tipoActual == SUMA) {
            if (auxDer != NULL && auxIzq != NULL) {
                (ar->symbol)->value = auxDer->value + auxIzq->value;
            } else if (auxDer == NULL && auxIzq != NULL) {   
                (ar->symbol)->value = (ar->right)->symbol->value + auxIzq->value;
            } else if(auxDer != NULL && auxIzq == NULL){
                (ar->symbol)->value = auxDer->value + (ar->left)->symbol->value;
            } else {
                (ar->symbol)->value = (ar->right)->symbol->value + (ar->left)->symbol->value;
            }
            
        }
        if (tipoActual == RESTA) {
            if (auxDer != NULL && auxIzq != NULL) {
                (ar->symbol)->value =  auxIzq->value - auxDer->value;
            } else if (auxDer == NULL && auxIzq != NULL) {   
                (ar->symbol)->value =  auxIzq->value - (ar->right)->symbol->value;
            } else if(auxDer != NULL && auxIzq == NULL){
                (ar->symbol)->value = (ar->left)->symbol->value - auxDer->value;
            } else {
                (ar->symbol)->value = (ar->left)->symbol->value - (ar->right)->symbol->value;
            }
            
        }
        if (tipoActual == PROD) {
            if (auxDer != NULL && auxIzq != NULL) {
                (ar->symbol)->value =  auxIzq->value * auxDer->value;
            } else if (auxDer == NULL && auxIzq != NULL) {   
                (ar->symbol)->value =  auxIzq->value * (ar->right)->symbol->value;
            } else if(auxDer != NULL && auxIzq == NULL){
                (ar->symbol)->value = (ar->left)->symbol->value * auxDer->value;
            } else {
                (ar->symbol)->value = (ar->left)->symbol->value * (ar->right)->symbol->value;
            }
            
        }

        if (tipoActual == EAND) {
            if (auxDer != NULL && auxIzq != NULL) {
                (ar->symbol)->value =  (auxIzq->value && auxDer->value);
            } else if (auxDer == NULL && auxIzq != NULL) {   
                (ar->symbol)->value =  (auxIzq->value && (ar->right)->symbol->value);
            } else if(auxDer != NULL && auxIzq == NULL){
                (ar->symbol)->value = (ar->left)->symbol->value && auxDer->value;
            } else {
                (ar->symbol)->value = ((ar->left)->symbol->value && (ar->right)->symbol->value);
            }
            
        }

        if (tipoActual == EOR) {
            if (auxDer != NULL && auxIzq != NULL) {
                (ar->symbol)->value =  (auxIzq->value || auxDer->value);
            } else if (auxDer == NULL && auxIzq != NULL) {   
                (ar->symbol)->value =  (auxIzq->value || (ar->right)->symbol->value);
            } else if(auxDer != NULL && auxIzq == NULL){
                (ar->symbol)->value = (ar->left)->symbol->value || auxDer->value;
            } else {
                (ar->symbol)->value = ((ar->left)->symbol->value || (ar->right)->symbol->value);
            } 
        }

        if (tipoActual == ENOT) {
            if (auxIzq != NULL) {   
                (ar->symbol)->value =  (auxIzq->value || (ar->right)->symbol->value);
            } else {
                (ar->symbol)->value = ((ar->left)->symbol->value || (ar->right)->symbol->value);
            } 
        }
    }
}
/*
// return (ar->right)->symbol->value + (ar->left)->symbol->value;
 if (tipoActual == SUMA || tipoActual == PROD || tipoActual == RESTA){
    // return (ar->right)->symbol->value  + (ar->left)->symbol->value;
    // return (ar->right)->symbol->value- (ar->left)->symbol->value;
    // return (ar->right)->symbol->value    * (ar->left)->symbol->value;
 }
*/
bool getError() {
    return err;
}



