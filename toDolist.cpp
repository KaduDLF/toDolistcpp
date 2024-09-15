#include <iostream>
#include <cstdio>
#include <limits>

using namespace std;

void menu(){
    cout << "Este é o menu de ações..." << endl;
    cout << "1 - adicione algo a Lista" << endl;
    cout << "2 - marque se foi feito" << endl;
    cout << "3 - consultar lista" << endl;
    cout << "4 - apagar lista" << endl;
    cout << "5 - sair do menu" << endl;
    cout << "=========================" << endl;
    cout << "Digite sua opção" << endl;
}

int main(){
    struct lista{
        char item[100];
        bool feito = false;
        int numItem;
    };
    struct lista list;
    int opcMenu, i, itemBusca, opcConsulta, opcApagar;
    char opc;
    i = 0;
    string saber;

    FILE *listaFazer;

    menu();
    cin >> opcMenu;
    while(opcMenu != 5){

        switch(opcMenu){
            case 1:
                system("cls");
                cout << "Deseja adicionar algo a lista? s para sim e n para não" << endl;
                cin >> opc;
                while(opc == 's'){
                    listaFazer = fopen("lista_a_fazer.dat", "rb");
                    if(fread(&list, sizeof(struct lista), 1, listaFazer) == 1){
                        while(!feof(listaFazer)){
                            i = list.numItem;
                            fread(&list, sizeof(struct lista), 1, listaFazer);
                        }
                        fclose(listaFazer);
                    }
                    cout << "i é: " << i << endl;
                    i++;
                    cout << "Vamos a adição..." << endl;
                    cin.get();

                    listaFazer = fopen("lista_a_fazer.dat", "ab+");
                    cout << "Digite um item: ";
                    cin >> list.item;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    list.numItem = i;
                    cout << "item " << i << endl;
                    fwrite(&list , sizeof(struct lista), 1, listaFazer);
                    fclose(listaFazer);

                    cout << "Deseja adicionar algo a mais na lista? s para sim e n para não" << endl;
                    cin >> opc;

                }
                break;
            case 2:
                system("cls");
                cout << "Deseja marcar algo da lista como feito? s para sim e n para não" << endl;
                cin >> opc;
                while(opc == 's'){
                    cout << "Digite o numero do item que você deseja marcar como feito" << endl;
                    cin >> itemBusca;
        
                       
                    listaFazer = fopen("lista_a_fazer.dat", "rb+");
                    if(listaFazer == NULL) {
                        cout << "Erro ao abrir o arquivo." << endl;
                        break;
                    }

                        
                    while(fread(&list, sizeof(struct lista), 1, listaFazer) == 1){
                        if(itemBusca == list.numItem){
                           list.feito = true; 

                            // Voltar a posição do ponteiro para sobrescrever o item atualizado
                            fseek(listaFazer, -sizeof(struct lista), SEEK_CUR);
                            fwrite(&list, sizeof(struct lista), 1, listaFazer);  // Escrever a atualização

                            cout << "Item marcado como feito com sucesso." << endl;
                            break;
                        }
                    }
                    cout << "Deseja marcar algo da lista como feito? s para sim e n para não" << endl;
                    cin >> opc;
                }
                break;
            
            case 3:
                system("cls");
                cout << "Qual opção deseja consultar?" << endl;
                cout << "1 - Mostrar toda a lista, Feitos ou não" << endl;
                cout << "2 - Mostrar apenas os que não foram feitos" << endl;
                cout << "3 - Mostrar os que foram feitos" << endl;
                cout << "4 - Sair" << endl;
                cin >> opcConsulta;

                while (opcConsulta != 4) {
                    switch (opcConsulta) {
                        case 1:
                            cout << "Todos os itens!" << endl << endl;
                            listaFazer = fopen("lista_a_fazer.dat", "rb");
                            if (listaFazer != NULL) {
                                while (fread(&list, sizeof(struct lista), 1, listaFazer) == 1) {
                                    saber = (list.feito) ? "Feito." : "Não Feito.";
                                    cout << list.numItem << " - " << list.item << " . " << saber << endl;
                                }
                                fclose(listaFazer);
                            } else {
                                cout << "Erro ao abrir o arquivo." << endl;
                            }
                            cin.get();
                            break;

                        case 2:
                            cout << "Não feitos!" << endl;
                            listaFazer = fopen("lista_a_fazer.dat", "rb");
                            if (listaFazer != NULL) {
                                while (fread(&list, sizeof(struct lista), 1, listaFazer) == 1) {
                                    if (!list.feito) {
                                        cout << list.numItem << " - " << list.item << " ." << endl;
                                    }
                                }
                                fclose(listaFazer);
                            } else {
                                cout << "Erro ao abrir o arquivo." << endl;
                            }
                            cin.get();
                            break;

                        case 3:
                            cout << "Feitos!" << endl;
                            listaFazer = fopen("lista_a_fazer.dat", "rb");
                            if (listaFazer != NULL) {
                                while (fread(&list, sizeof(struct lista), 1, listaFazer) == 1) {
                                    if (list.feito) {
                                        cout << list.numItem << " - " << list.item << " ." << endl;
                                    }
                                }
                                fclose(listaFazer);
                            } else {
                                cout << "Erro ao abrir o arquivo." << endl;
                            }
                            cin.get();
                            break;

                        default:
                            cout << "Opção inválida" << endl;
                            break;
                    }

                    
                    cout << "Qual opção deseja consultar?" << endl;
                    cout << "1 - Mostrar toda a lista, Feitos ou não" << endl;
                    cout << "2 - Mostrar apenas os que não foram feitos" << endl;
                    cout << "3 - Mostrar os que foram feitos" << endl;
                    cout << "4 - Sair" << endl;
                    cin >> opcConsulta;
                }
                break;
            case 4:
                system("cls");
                cout << "Realmente deseja apagar a lista? 1 para sim e 2 para não!" << endl;
                cin >> opcApagar;
                
                if(opcApagar == 1){
                    listaFazer = fopen("lista_a_fazer.dat", "wb");
                    if(listaFazer == NULL){
                        cout << "Lista não apagada" << endl;
                    }else{
                        cout << "Lista apagada com sucesso!" << endl;
                    }
                    fclose(listaFazer);
                    
                }else{
                    cout << "lista não apagada" << endl;
                }
                break;
            default:
                cout << "opção invalida!" << endl;
                break;
        }
        menu();
        cin >> opcMenu;
    }
}