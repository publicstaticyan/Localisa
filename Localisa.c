#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* 
* Sistema funcional de write e read de arquivo.                                                     OK
* CRUD - Fazer Funcionalidade de Deletar                                                            OK
* CRUD - Veiculos                                                                                   OK
* CRUD - Locações                                                                                   OK
*
* FUNCÃO - Dar Baixa                                                                                OK
*
* Diminuir Tamanho das Funções de CRUD, Substituir por C(); R(); U(); D(); char como param. (Não, obrigado.)
*
* BUG CRUD - String Pegando Espaços                                                                 OK
* BUG Register Cliente - Deletar Depois Registrar Cria Codigo Repetido                              OK
*/

/*

* CLIENTE = código, nome, endereço, telefone 

* VEÍCULO = código do veículo, descrição, modelo, cor, placa, valor diária, quantidade de 
ocupantes, status

* LOCAÇÃO = código da locação, data de retirada, data de devolução, seguro, quantidade de dias, 
código do cliente, código do veículo 

*/

int hour = -1, day = 0;

struct sClients { char code[50]; char name[50]; char address[50]; char phone[50]; };
typedef struct sClients tClients; tClients vetClients[1000];

struct sVehicles { char code[50]; char desc[50]; char model[50]; char color[50]; char plate[50]; char daily_value[50]; char occupants_quantity[50]; char status[50]; };
typedef struct sVehicles tVehicles; tVehicles vetVehicles[1000];

struct sLeases { char code[50]; char lease_day[50]; char return_day[50]; char insurance[50]; char total_value[50]; char days[50]; char client_code[50]; char vehicle_code[50]; };
typedef struct sLeases tLeases; tLeases vetLeases[1000];

// --------------------------------------------------------------------------------------------------------------------- //

int main() {

    loadFile('c'); // Load Clients Files
    loadFile('v'); // Load Vehicles Files
    loadFile('l'); // Load Leases Files

    insertDate(); // * Coloca o Usuário na primeira pagina do programa.

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------- //

void printLogo() {

printf("\n                        /$$                                     /$$ /$$                    ");
printf("\n                       | $$                                    | $$|__/                    ");
printf("\n                       | $$        /$$$$$$   /$$$$$$$  /$$$$$$ | $$ /$$  /$$$$$$$  /$$$$$$ ");
printf("\n                       | $$       /$$__  $$ /$$_____/ |____  $$| $$| $$ /$$_____/ |____  $$");
printf("\n                       | $$      | $$  | $$| $$        /$$$$$$$| $$| $$|  $$$$$$   /$$$$$$$");
printf("\n                       | $$      | $$  | $$| $$       |$$__  $$| $$| $$ |____  $$ /$$__  $$");
printf("\n                       | $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$| $$ /$$$$$$$/|  $$$$$$$");
printf("\n                       |________/ |______/  |_______/ |_______/|__/|__/|_______/  |_______/\n\n\n");    

}

void arrowPrint(int pos, int selec) {
    if (pos == selec) {
        printf(">> ");
    } else {
        printf("");
    }
}

void insertDate() {
    int day_now = 0, month_now = 0;
    while(hour > 23 || hour < 0) {
        system("cls");
        printf("Insira a hora atual sem os minutos por favor: ");
        scanf("%d", &hour);
    }

    while (day_now < 1 || day_now > 31) {
        system("cls");
        printf("Insira o numero do dia atual: ");
        scanf("%d", &day_now);
    }

    while (month_now < 1 || month_now > 12) {
        system("cls");
        printf("Insira o numero do mes atual: ");
        scanf("%d", &month_now);
    }

    system("cls");
    day = ((month_now - 1) * 31) + day_now;
    if (day > 365) {
        day = 365;
    }
    printf("\nDATA DO PROGRAMA: \n(assumindo que todos os meses tem 31 dias)\n\n-Dia: %d\n-Mes: %d\n-Hora: %d:00\n-Dia do Ano: %d\n\n", day_now, month_now, hour, day);
    printf("Pressione qualquer tecla para prosseguir...");
    getch();
    menuInit();
}

// --------------------------------------------------------------------------------------------------------------------- //

void menuInit() {
    int setaPos = 1; int teclaPress = 0;

    while(teclaPress != 13) { // 13 = ENTER
        system("cls");

        printLogo();

        printf("                                                      "); arrowPrint(1, setaPos); printf("CLIENTES\n\n");
        printf("                                                      "); arrowPrint(2, setaPos); printf("VEICULOS\n\n");
        printf("                                                      "); arrowPrint(3, setaPos); printf("LOCACOES\n\n\n");
        printf("                                                      "); arrowPrint(4, setaPos); printf("DEBUG\n\n");
        printf("              Utilize as setas do teclado para subir e descer as opcoes, aperter ENTER para selecionar.");

        // * Diferente do Scanf, Getch pega qualquer input to teclado

        teclaPress = getch(); 
        if (teclaPress == 80 && setaPos != 4) { // Tecla 80: Seta pra baixo
            setaPos++;
        } else if (teclaPress == 72 && setaPos != 1) {  // Tecla 72: Seta pra cima
            setaPos--;
        } else {
            setaPos = setaPos;
        }
    }

    switch (setaPos) {
    case 1:
        menuClients();
        break;
    case 2:
        menuVehicles();
        break;
    case 3:
        menuLeases();
        break;
    case 4:
        //debug();
        break;
    }
}

void menuClients() {
    int setaPos = 1;
    int teclaPress = 0;

    while(teclaPress != 13) { // 13 = ENTER
        system("cls");

        printLogo();

        printf("                                                   "); arrowPrint(1, setaPos); printf("CADASTRAR\n\n");
        printf("                                                   "); arrowPrint(2, setaPos); printf("LISTAR TODOS OS CLIENTES\n\n");
        printf("                                                   "); arrowPrint(3, setaPos); printf("ALTERAR DADOS\n\n");
        printf("                                                   "); arrowPrint(4, setaPos); printf("EXCLUIR CLIENTE\n\n\n");
        printf("                                                   "); arrowPrint(5, setaPos); printf("VOLTAR\n\n\n");
        printf("              Utilize as setas do teclado para subir e descer as opcoes, aperter ENTER para selecionar.");

        teclaPress = getch(); 
        if (teclaPress == 80 && setaPos != 5) { // Tecla 80: Seta pra baixo
            setaPos++;
        } else if (teclaPress == 72 && setaPos != 1) {  // Tecla 72: Seta pra cima
            setaPos--;
        } else {
            setaPos = setaPos;
        }
    }

    switch (setaPos) {
    case 1:
        registerClient();
        break;
    case 2:
        listClient();
        break;
    case 3:
        changeClient();
        break;
    case 4:
        deleteClient();
        break;
    case 5:
        menuInit();
        break;
    }
}

void menuVehicles() {
    int setaPos = 1;
    int teclaPress = 0;

    while(teclaPress != 13) { // 13 = ENTER
        system("cls");

        printLogo();

        printf("                                                   "); arrowPrint(1, setaPos); printf("CADASTRAR\n\n");
        printf("                                                   "); arrowPrint(2, setaPos); printf("LISTAR TODOS OS VEICULOS\n\n");
        printf("                                                   "); arrowPrint(3, setaPos); printf("ALTERAR DADOS\n\n");
        printf("                                                   "); arrowPrint(4, setaPos); printf("EXCLUIR VEICULO\n\n\n");
        printf("                                                   "); arrowPrint(5, setaPos); printf("VOLTAR\n\n\n");
        printf("              Utilize as setas do teclado para subir e descer as opcoes, aperter ENTER para selecionar.");

        teclaPress = getch(); 
        if (teclaPress == 80 && setaPos != 5) { // Tecla 80: Seta pra baixo
            setaPos++;
        } else if (teclaPress == 72 && setaPos != 1) {  // Tecla 72: Seta pra cima
            setaPos--;
        } else {
            setaPos = setaPos;
        }
    }

    switch (setaPos) {
    case 1:
        registerVehicle();
        break;
    case 2:
        listVehicles();
        break;
    case 3:
        changeVehicle();
        break;
    case 4:
        deleteVehicle();
        break;
    case 5:
        menuInit();
        break;
    }
}

void menuLeases() {
    if (hour >= 8 && hour <= 18) {
    int setaPos = 1;
    int teclaPress = 0;

    while(teclaPress != 13) { // 13 = ENTER
        system("cls");

        printLogo();

        printf("                                                   "); arrowPrint(1, setaPos); printf("CADASTRAR LOCACAO\n\n");
        printf("                                                   "); arrowPrint(2, setaPos); printf("DAR BAIXA\n\n");
        printf("                                                   "); arrowPrint(3, setaPos); printf("PESQUISA CLIENTE\n\n");
        printf("                                                   "); arrowPrint(4, setaPos); printf("PREMIO\n\n");
        printf("                                                   "); arrowPrint(5, setaPos); printf("VOLTAR\n\n\n");
        printf("              Utilize as setas do teclado para subir e descer as opcoes, aperter ENTER para selecionar.");

        teclaPress = getch(); 
        if (teclaPress == 80 && setaPos != 5) { // Tecla 80: Seta pra baixo
            setaPos++;
        } else if (teclaPress == 72 && setaPos != 1) {  // Tecla 72: Seta pra cima
            setaPos--;
        } else {
            setaPos = setaPos;
        }
    }

    switch (setaPos) {
    case 1:
        registerLease();
        break;
    case 2:
        baixaLease();
        break;
    case 3:
        pesquisaCliente();
        break;
    case 4:
        calculaPremio();
        break;
    case 5:
        menuInit();
        break;
        }
    } else {
        system("cls");
        printf("Cadastro de Locacoes fora do horario comercial proibido.\n\nPressione qualquer tecla para retornar ao menu principal...");
        getch();
        menuInit();
    }
}

// --------------------------------------------------------------------------------------------------------------------- //

// Crud Clients

void registerClient() { // OK 
    system("cls");

    char rcode[50]; char rname[50]; char raddress[50]; char rphone[50];

    printf("\n ================================ \n CADASTRAMENTO DE NOVO CLIENTE \n ================================ \n\n Telefone: ");

    scanf("%[^\n]s", &rphone);
    fflush(stdin);

    int clientExists = find(1, rphone);

    if (clientExists == 0) {
        printf("\n Endereco: ");
        scanf("%[^\n]s", &raddress);
        fflush(stdin);

        printf("\n Nome: ");
        scanf("%[^\n]s", &rname);
        fflush(stdin);

        int available_pos = 0;

        while (strcmp(vetClients[available_pos].code, "EOF") != 0) {
            available_pos++;
        }

        int new_code = atoi(vetClients[available_pos - 1].code);
        new_code++;

        // int new_code = position + 1; // BUG Aqui. Codigo deve ser criado pegando o ultimo codigo e convertendo atoi

        // int available_pos = position;

        itoa(new_code, rcode, 10);

        strcpy(vetClients[available_pos].code, rcode);
        strcpy(vetClients[available_pos].address, raddress);
        strcpy(vetClients[available_pos].name, rname);
        strcpy(vetClients[available_pos].phone, rphone);

        strcpy(vetClients[available_pos + 1].code, "EOF");

        saveFile('c');

        system("cls");

        printf("\n ================================ \n Cliente Cadastrado! \n ================================ \n\n Nome: %s\n Endereco: %s\n Telefone: %s\n Codigo: %s\n", rname, raddress, rphone, rcode);
        printf("\n Pressione qualquer tecla para retornar ao menu de clientes...");
        getch();
        menuClients();

    } else {
        system("cls");
        printf("\n !!! Esse cliente ja foi cadastrado no sistema. !!! \n");
        printf("\n Pressione qualquer tecla para retornar ao menu de clientes...\n");
        getch();
        menuClients();
    }
}

void listClient() { // OK
    system("cls");

    printf("\n================================ \n LISTAGEM DE CLIENTES \n================================ \n\n");

    for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
        printf("\nCodigo: %s | Nome: %s | Endereco: %s |  Telefone: %s \n", vetClients[i].code, vetClients[i].name, vetClients[i].address, vetClients[i].phone);
    }

    printf("\nPressione qualquer tecla para retornar ao menu de clientes...");
    getch();
    menuClients();
}

void changeClient() { // OK
    system("cls");

    char code_selected[50]; char new_name[50]; char new_address[50]; char new_phone[50];

    for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
        printf("\nCodigo: %s | Nome: %s | Endereco: %s |  Telefone: %s \n", vetClients[i].code, vetClients[i].name, vetClients[i].address, vetClients[i].phone);
    }

    printf("\n================================ \n ALTERACAO DE DADOS (CLIENTE) \n================================ \n\n");

    printf("\nDigite o codigo do cliente que deseja alterar os dados:\n");
    scanf("%s", &code_selected);
    fflush(stdin);

    int exists = 0; int client_position = 0;

    for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0 && exists == 0; i++) {
        if (strcmp(vetClients[i].code, code_selected) == 0) {
            exists = 1;
            client_position = i;
        }
    }

    if (exists == 1) {

        printf("\nCliente Selecionado:\n- Codigo: %s\n- Nome: %s\n- Endereco: %s\n- Telefone: %s\n\n", vetClients[client_position].code, vetClients[client_position].name, vetClients[client_position].address, vetClients[client_position].phone);
        
        printf("Digite o novo nome do cliente:\n");
        scanf("%[^\n]s", &new_name);
        fflush(stdin);

        printf("\nDigite o novo endereco do cliente:\n");
        scanf("%[^\n]s", &new_address);
        fflush(stdin);

        printf("\nDigite o novo telefone do cliente:\n");
        scanf("%[^\n]s", &new_phone);
        fflush(stdin);

        strcpy(vetClients[client_position].name, new_name);
        strcpy(vetClients[client_position].address, new_address);
        strcpy(vetClients[client_position].phone, new_phone);

        saveFile('c');

        printf("\n\nCliente atualizado!\n- Novo Nome: %s\n- Novo Endereco: %s\n- Novo Telefone: %s\n", new_name, new_address, new_phone);
        printf("\n\nPressione qualquer tecla para retornar ao menu de clientes.");
        getch();
        menuClients();

    } else {
        printf("\n!!! O codigo de cliente digitado nao foi encontrado. !!!\nPressione qualquer tecla para retornar ao menu de clientes.");
        getch();
        menuClients();
    }
}

void deleteClient() { // OK
    system("cls");

    for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
        printf("\nCodigo: %s | Nome: %s | Endereco: %s |  Telefone: %s \n", vetClients[i].code, vetClients[i].name, vetClients[i].address, vetClients[i].phone);
    }

    printf("\n================================ \n DELETAR CLIENTES \n================================ \n\n");

    char code_selected[50];

    printf("Digite o codigo do cliente que deseja deletar:\n");
    scanf("%s", &code_selected);
    fflush(stdin);

    int exists = 0; int client_position = 0;

    for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0 && exists == 0; i++) {
        if (strcmp(vetClients[i].code, code_selected) == 0) {
            exists = 1;
            client_position = i;
        }
    }

    if (exists == 1) {

        strcpy(vetClients[client_position].code, "");
        strcpy(vetClients[client_position].name, "");
        strcpy(vetClients[client_position].address, "");
        strcpy(vetClients[client_position].phone, "");
        
        saveFile('c');
        loadFile('c');

        printf("\n\nCliente deletado!\n");
        printf("\n\nPressione qualquer tecla para retornar ao menu de clientes.");
        getch();
        menuClients();
    } else {
        printf("\n!!! O codigo de cliente digitado nao foi encontrado. !!!\nPressione qualquer tecla para retornar ao menu de clientes.");
        getch();
        menuClients();
    }
}

// --------------------------------------------------------------------------------------------------------------------- //

// Crud Vehicles

void registerVehicle() {
    system("cls");

    char rcode[50]; char rstatus[50]; // Setados Automaticamente
    char rplate[50]; char rmodel[50]; char rcolor[50];  char rdesc[50]; char rdaily_value[50]; char roccupants[50];

    printf("\n ================================ \n CADASTRAMENTO DE NOVO VEICULO \n ================================ \n\n Placa: ");

    scanf("%[^\n]s", &rplate);
    fflush(stdin);

    int vehicleExists = find(2, rplate);
    // Testar Função Nova

    if (vehicleExists == 0) { // !! BUG !! 
        printf("\n Modelo: ");
        scanf("%[^\n]s", &rmodel);
        fflush(stdin);

        printf("\n Cor: ");
        scanf("%[^\n]s", &rcolor);
        fflush(stdin);

        printf("\n Descricao: ");
        scanf("%[^\n]s", &rdesc);
        fflush(stdin);

        printf("\n Valor da Diaria: ");
        scanf("%[^\n]s", &rdaily_value);
        fflush(stdin);

        printf("\n Numero de Ocupantes: ");
        scanf("%[^\n]s", &roccupants);
        fflush(stdin);

        int position = 0;

        while (strcmp(vetVehicles[position].code, "EOF") != 0) {
            position++;
        }

        int new_code = position + 1; // Debugar

        int available_pos = position;

        itoa(new_code, rcode, 10);

        strcpy(vetVehicles[available_pos].code, rcode);
        strcpy(vetVehicles[available_pos].status, "Disponivel");
        strcpy(vetVehicles[available_pos].plate, rplate);
        strcpy(vetVehicles[available_pos].model, rmodel);
        strcpy(vetVehicles[available_pos].color, rcolor);
        strcpy(vetVehicles[available_pos].desc, rdesc);
        strcpy(vetVehicles[available_pos].daily_value, rdaily_value);
        strcpy(vetVehicles[available_pos].occupants_quantity, roccupants);

        strcpy(vetVehicles[available_pos + 1].code, "EOF");

        saveFile('v');

        system("cls");

        printf("\n ================================ \n Veiculo Cadastrado! \n ================================ \n\n Codigo: %s\n Status: Disponivel\n Placa: %s\n Modelo: %s\n Cor: %s\n Descricao: %s\n Valor da Diaria: %s\n Quantidade de Ocupantes: %s\n", rcode, rplate, rmodel, rcolor, rdesc, rdaily_value, roccupants);
        printf("\n Pressione qualquer tecla para retornar ao menu de veiculos...");
        getch();
        menuVehicles();

    } else {
        system("cls");
        printf("\n !!! Esse veiculo ja foi cadastrado no sistema. !!! \n");
        printf("\n Pressione qualquer tecla para retornar ao menu de veiculos...\n");
        getch();
        menuVehicles();
    }
} 

void listVehicles() {
    system("cls");

    printf("\n================================ \n LISTAGEM DE VEICULOS \n================================ \n\n");

    for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0; i++) {
        printf("\nCodigo: %s | Status: %s | Placa: %s | Modelo: %s | Cor: %s | Descricao: %s | Valor da Diaria: %s | Quantidade de Ocupantes: %s\n", vetVehicles[i].code, vetVehicles[i].status, vetVehicles[i].plate, vetVehicles[i].model, vetVehicles[i].color, vetVehicles[i].desc, vetVehicles[i].daily_value, vetVehicles[i].occupants_quantity);
    }

    printf("\nPressione qualquer tecla para retornar ao menu de veiculos...");
    getch();
    menuVehicles();
}

void changeVehicle() {
    system("cls");

    char code_selected[50];
    char new_plate[50]; char new_model[50]; char new_color[50];  char new_desc[50]; char new_daily_value[50]; char new_occupants[50];

    for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0; i++) {
        printf("\nCodigo: %s | Status: %s | Placa: %s | Modelo: %s | Cor: %s | Descricao: %s | Valor da Diaria: %s | Quantidade de Ocupantes: %s\n", vetVehicles[i].code, vetVehicles[i].status, vetVehicles[i].plate, vetVehicles[i].model, vetVehicles[i].color, vetVehicles[i].desc, vetVehicles[i].daily_value, vetVehicles[i].occupants_quantity);
    }

    printf("\n================================ \n ALTERACAO DE DADOS (VEICULO) \n================================ \n\n");

    printf("\nDigite o codigo do veiculo que deseja alterar os dados:\n");
    scanf("%s", &code_selected);
    fflush(stdin);

    int exists = 0; int vehicle_position = 0;

    for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0 && exists == 0; i++) {
        if (strcmp(vetVehicles[i].code, code_selected) == 0) {
            exists = 1;
            vehicle_position = i;
        }
    }

    if (exists == 1) {
        printf("\nVeiculo Selecionado:\n- Codigo: %s\n- Status: %s\n- Placa: %s\n- Modelo: %s\n- Cor: %s\n- Descricao: %s\n- Valor da Diaria: %s\n- Quantidade de Ocupantes: %s\n", vetVehicles[vehicle_position].code, vetVehicles[vehicle_position].status, vetVehicles[vehicle_position].plate, vetVehicles[vehicle_position].model, vetVehicles[vehicle_position].color, vetVehicles[vehicle_position].desc, vetVehicles[vehicle_position].daily_value, vetVehicles[vehicle_position].occupants_quantity);
        
        printf("\nDigite os novos dados do veiculo:\n");

        printf("\n Placa: ");
        scanf("%[^\n]s", &new_plate);
        fflush(stdin);

        printf("\n Modelo: ");
        scanf("%[^\n]s", &new_model);
        fflush(stdin);

        printf("\n Cor: ");
        scanf("%[^\n]s", &new_color);
        fflush(stdin);

        printf("\n Descricao: ");
        scanf("%[^\n]s", &new_desc);
        fflush(stdin);

        printf("\n Valor da Diaria: ");
        scanf("%[^\n]s", &new_daily_value);
        fflush(stdin);

        printf("\n Numero de Ocupantes: ");
        scanf("%[^\n]s", &new_occupants);
        fflush(stdin);

        strcpy(vetVehicles[vehicle_position].plate, new_plate);
        strcpy(vetVehicles[vehicle_position].model, new_model);
        strcpy(vetVehicles[vehicle_position].color, new_color);
        strcpy(vetVehicles[vehicle_position].desc, new_desc);
        strcpy(vetVehicles[vehicle_position].daily_value, new_daily_value);
        strcpy(vetVehicles[vehicle_position].occupants_quantity, new_occupants);

        saveFile('v');

        printf("\n\nVeiculo atualizado!\n- Nova Placa: %s\n- Novo Modelo: %s\n- Nova Cor: %s\n- Nova Descricao: %s\n- Novo Valor da Diaria: %s\n- Novo Valor de Ocupantes: %s\n", new_plate, new_model, new_color, new_desc, new_daily_value, new_occupants);
        printf("\n\nPressione qualquer tecla para retornar ao menu de veiculos.");
        getch();
        menuVehicles();

    } else {
        printf("\n!!! O codigo de veiculo digitado nao foi encontrado. !!!\nPressione qualquer tecla para retornar ao menu de veiculos.");
        getch();
        menuVehicles();
    }
}

void deleteVehicle() {
    system("cls");

    for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0; i++) {
        printf("\nCodigo: %s | Status: %s | Placa: %s | Modelo: %s | Cor: %s | Descricao: %s | Valor da Diaria: %s | Quantidade de Ocupantes: %s\n", vetVehicles[i].code, vetVehicles[i].status, vetVehicles[i].plate, vetVehicles[i].model, vetVehicles[i].color, vetVehicles[i].desc, vetVehicles[i].daily_value, vetVehicles[i].occupants_quantity);
    }

    printf("\n================================ \n DELETAR VEICULOS \n================================ \n\n");

    char code_selected[50];

    printf("Digite o codigo do veiculo que deseja deletar:\n");
    scanf("%s", &code_selected);
    fflush(stdin);

    int exists = 0; int vehicle_position = 0;

    for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0 && exists == 0; i++) {
        if (strcmp(vetVehicles[i].code, code_selected) == 0) {
            exists = 1;
            vehicle_position = i;
        }
    }

    if (exists == 1) {

        strcpy(vetVehicles[vehicle_position].code, "");
        strcpy(vetVehicles[vehicle_position].status, "");
        strcpy(vetVehicles[vehicle_position].plate, "");
        strcpy(vetVehicles[vehicle_position].desc, "");
        strcpy(vetVehicles[vehicle_position].color, "");
        strcpy(vetVehicles[vehicle_position].model, "");
        strcpy(vetVehicles[vehicle_position].daily_value, "");
        strcpy(vetVehicles[vehicle_position].occupants_quantity, "");
        
        saveFile('v');
        loadFile('v');

        printf("\n\nVeiculo deletado!\n");
        printf("\n\nPressione qualquer tecla para retornar ao menu de veiculos.");
        getch();
        menuVehicles();
    } else {
        printf("\n!!! O codigo de veiculo digitado nao foi encontrado. !!!\nPressione qualquer tecla para retornar ao menu de veiculos.");
        getch();
        menuVehicles();
    }
}

// --------------------------------------------------------------------------------------------------------------------- //

// Crud Leases

void registerLease() {
    char selected_code[50]; int day_back = -1; int month_back = -1; int occupant_needed = 0; int exists = 0;

    int client_pos = 0;

    while (exists == 0) {
        system("cls");
        for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
            printf("\nCodigo: %s | Nome: %s | Endereco: %s |  Telefone: %s \n", vetClients[i].code, vetClients[i].name, vetClients[i].address, vetClients[i].phone);
        }

        printf("\n==================================================================\nPor favor, insira abaixo um codigo VALIDO do cliente que deseja selecionar para cadastrar uma locacao:\n");
        scanf("%s", &selected_code);
        fflush(stdin);

        for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
            if (strcmp(vetClients[i].code, selected_code) == 0) {
                exists = 1;
                client_pos = i;
            }
        }
    }

    system("cls");
    fflush(stdin);

    int day_verify = -1; int day_valid = 0;

    while (day_valid == 0) {

        while (month_back < 1 || month_back > 12) {
            system("cls");
            printf("Em qual mes sera a devolucao do veiculo?\n");
            scanf("%d", &month_back);
            fflush(stdin);
        }

        while (day_back < 1 || day_back > 31) {
            system("cls");
            printf("Em qual dia desse mes sera a devolucao do veiculo?\n");
            scanf("%d", &day_back);
            fflush(stdin);
        }

        day_verify = ((month_back - 1) * 31) + day_back;

        if (day_verify < day) {
            printf("\nO dia inserido ja passou. Por favor insira uma data valida.");
            month_back= -1; day_back= -1;
            sleep(2);
        } else {
            day_valid = 1;
        }
    }

    system("cls");
    printf("Qual a quantidade de ocupantes do veiculo necessaria?\n");
    scanf("%d", &occupant_needed);

    int existe_vehicle = 0; int vehicle_pos = 0;

    for (int i = 0; (strcmp(vetVehicles[i].code, "EOF") != 0) && existe_vehicle == 0; i++) {
        int ocuppants_available = atoi(vetVehicles[i].occupants_quantity);

        if ((strcmp(vetVehicles[i].status, "Disponivel") == 0) && (occupant_needed <= ocuppants_available)) {
            existe_vehicle = 1;
            vehicle_pos = i;
        }
    }

    if (existe_vehicle == 1) {

        int vehicle_days = day_verify - day;
        int valorDiariaTotal = vehicle_days * atoi(vetVehicles[vehicle_pos].daily_value);

        int option_insurance = -1;

        while ((option_insurance < 0) || (option_insurance > 1)) {

        system("cls");
        printf("\nVeiculo alocado!\n\n");
        printf("Dados do Veiculo:\n- Codigo: %s\n- Modelo: %s\n- Cor: %s\n\n", vetVehicles[vehicle_pos].code, vetVehicles[vehicle_pos].model, vetVehicles[vehicle_pos].color);
        printf("Dados do Cliente:\n- Codigo: %s\n- Nome: %s\n- Telefone: %s\n\n", vetClients[client_pos].code, vetClients[client_pos].name, vetClients[client_pos].phone);
        printf("Valor Total de Diarias: %d\n", valorDiariaTotal);

        printf("Deseja adicionar um seguro de 50 reais ao veiculo? Digite 1 se quiser e 0 se nao.\n");
        fflush(stdin);
        scanf("%d", &option_insurance);
        }

        // struct sLeases { char code[50]; char lease_day[50]; char return_day[50]; char insurance[50]; char days[50]; char client_code[50]; char vehicle_code[50]; };
        // typedef struct sLeases tLeases; tLeases vetLeases[1000];

        int available_pos = 0;

        while (strcmp(vetLeases[available_pos].code, "EOF") != 0) {
            available_pos++;
        }

        int new_code = atoi(vetLeases[available_pos - 1].code);
        new_code++;

        char rcode[50];
        char rlease_day[50];
        char rreturn_day[50];
        char rdays[50];

        char rtotal_value[50];
        itoa(new_code, rcode, 10);
        itoa(day_verify, rreturn_day, 10);
        itoa(day, rlease_day, 10);
        itoa(vehicle_days, rdays, 10);
        itoa(valorDiariaTotal, rtotal_value, 10);

        if (option_insurance == 0) {
            strcpy(vetLeases[available_pos].code, rcode);
            strcpy(vetLeases[available_pos].lease_day, rlease_day);
            strcpy(vetLeases[available_pos].return_day, rreturn_day);
            strcpy(vetLeases[available_pos].insurance, "Nao");
            strcpy(vetLeases[available_pos].days, rdays);
            strcpy(vetLeases[available_pos].total_value, rtotal_value);
            strcpy(vetLeases[available_pos].client_code, vetClients[client_pos].code);
            strcpy(vetLeases[available_pos].vehicle_code, vetVehicles[vehicle_pos].code);

            strcpy(vetVehicles[vehicle_pos].status, "Alugado");

            strcpy(vetLeases[available_pos + 1].code, "EOF");

            saveFile('l');
            loadFile('l');
            saveFile('v');
            loadFile('v');
            printf("\nAperte qualquer tecla para voltar ao menu de locacoes.\n");
            getch();
            menuLeases();
        } else {
        valorDiariaTotal = valorDiariaTotal + 50;
        itoa(valorDiariaTotal, rtotal_value, 10);
            strcpy(vetLeases[available_pos].code, rcode);
            strcpy(vetLeases[available_pos].lease_day, rlease_day);
            strcpy(vetLeases[available_pos].return_day, rreturn_day);
            strcpy(vetLeases[available_pos].insurance, "Sim");
            strcpy(vetLeases[available_pos].days, rdays);
            strcpy(vetLeases[available_pos].total_value, rtotal_value);
            strcpy(vetLeases[available_pos].client_code, vetClients[client_pos].code);
            strcpy(vetLeases[available_pos].vehicle_code, vetVehicles[vehicle_pos].code);

            strcpy(vetVehicles[vehicle_pos].status, "Alugado");

            strcpy(vetLeases[available_pos + 1].code, "EOF");
        printf("\nValor Total final das diarias: %d\n", valorDiariaTotal);
        printf("\nAperte qualquer tecla para voltar ao menu de locacoes.\n");
        saveFile('l');
        loadFile('l');
        saveFile('v');
        loadFile('v');
        getch();
        menuLeases();
        }
    } else {
        system("cls");
        printf("\nNenhum veiculo com os requerimentos inseridos anteriormente foi encontrado disponivel para locacao.\n\nVerifique a listagem de veiculos no menu 'VEICULOS'.\n\nPressione qualquer botao para retornar ao menu de locacoes...");
        getch();
        menuLeases();
    }

    // Varrer Vetor de Veiculos Procurando por Status:Disponivel && Ocuppants:&occupant OK

    // TotalDiarias = (Data de Entrega - Data de Retirada) * PreçoDaDiaria OK

    // Contratar Seguro? Valor de 50$. ValorTotal = TotalDiarias + Seguro; OK

    // Insere Lease no Vetor de Leases passando Codigo do Cliente, Codigo do Veiculo, Valor a ser pago. OK
    
}

void baixaLease() {
    system("cls");

// sLeases { char code[50]; char lease_day[50]; char return_day[50]; char insurance[50]; char total_value[50]; char days[50]; char client_code[50]; char vehicle_code[50]; };

    int exists = 0; char selected_code[50]; int lease_pos = 0;

    while (exists == 0) { 

        for (int i = 0; strcmp(vetLeases[i].code, "EOF") != 0; i++) {
            printf("\nCodigo: %s | Dia da Locacao: %s | Dia do Retorno: %s | Seguro: %s | Valor Total: %s | Dias Alugados: %s | Codigo do Cliente: %s | Codigo do Veiculo: %s\n", vetLeases[i].code, vetLeases[i].lease_day, vetLeases[i].return_day, vetLeases[i].insurance, vetLeases[i].total_value, vetLeases[i].days, vetLeases[i].client_code, vetLeases[i].vehicle_code);
        }

        printf("\n==================================================================\nPor favor, insira abaixo um codigo VALIDO da locacao que deseja dar baixa:\n");
        scanf("%s", &selected_code);
        fflush(stdin);

        for (int i = 0; strcmp(vetLeases[i].code, "EOF") != 0; i++) {
            if (strcmp(vetLeases[i].code, selected_code) == 0) {
                exists = 1;
                lease_pos = i;
            }
        }
        system("cls");
    }

    printf("\nDando baixa na locacao:\n\nCodigo: %s\nValor a ser pago: %s\nDias Alugados: %s\nCodigo do cliente: %s\nCodigo do veiculo: %s\n", vetLeases[lease_pos].code, vetLeases[lease_pos].total_value, vetLeases[lease_pos].days, vetLeases[lease_pos].client_code, vetLeases[lease_pos].vehicle_code);

    int return_date = atoi(vetLeases[lease_pos].return_day);
    int total_multa = 0;

    if (day > return_date) {

        int daily_value = atoi(vetLeases[lease_pos].total_value) / atoi(vetLeases[lease_pos].days);

        printf("Daily Value: %d", daily_value);
        
        int difference_value = (day - return_date) * 30;

        total_multa = difference_value + (atoi(vetLeases[lease_pos].total_value) * 5/100);
    }

    printf("\n\nMulta!\nTotal recalculado com multa: %d", total_multa); // Talvez o valor esteja errado

    int vehicle_pos = 0;

    for (int i = 0; strcmp(vetVehicles[i].code, vetLeases[lease_pos].vehicle_code) != 0; i++) {
        vehicle_pos = i;
    }

    strcpy(vetLeases[lease_pos].code, "");
    strcpy(vetLeases[lease_pos].lease_day, "");
    strcpy(vetLeases[lease_pos].return_day, "");
    strcpy(vetLeases[lease_pos].insurance, "");
    strcpy(vetLeases[lease_pos].days, "");
    strcpy(vetLeases[lease_pos].total_value, "");
    strcpy(vetLeases[lease_pos].client_code, "");
    strcpy(vetLeases[lease_pos].vehicle_code, "");

    strcpy(vetVehicles[vehicle_pos].status, "Disponivel");

    printf("\nBaixa dada!\n");
    printf("\nAperte qualquer tecla para retornar ao menu original.\n");

    saveFile('l');
    loadFile('l');
    saveFile('v');
    loadFile('v');
    getch();
    menuLeases();
}

void pesquisaCliente() {
    int exists_flag = 0; char selected_client[50];

    while (exists_flag == 0) {
        system("cls");
        printf("\n================================ \n LISTAGEM DE CLIENTES \n================================ \n\n");

        for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
            printf("\nCodigo: %s | Nome: %s | Endereco: %s |  Telefone: %s \n", vetClients[i].code, vetClients[i].name, vetClients[i].address, vetClients[i].phone);
        }

        printf("\nDigite o codigo do cliente que deseja ver as locacoes:\n");
        scanf("%s", &selected_client);

        for (int i = 0; strcmp(vetClients[i].code, selected_client) != 0; i++) {
            if (strcmp(vetClients[i].code, selected_client) == 0) {
                exists_flag = 0;
                printf("tomanucu");
            }
        }
    }

    system("cls");

    for (int i = 0; strcmp(vetLeases[i].code, "EOF") != 0; i++) {
        if (strcmp(vetLeases[i].client_code, selected_client) == 0) {
            printf("\nLocacao: %s\nCliente: %s\nVeiculo: %s\n", vetLeases[i].code, vetLeases[i].client_code, vetLeases[i].vehicle_code);
        }
    }
}

void calculaPremio() {
    for (int i = 0; strcmp(vetLeases[i].code, "EOF") != 0; i++) {
        int dias = atoi(vetLeases[i].days);
        if ((dias * 10) >= 500) {
            int client = 0;
            for (int a = 0; strcmp(vetClients[a].code, vetLeases[i].client_code) != 0; a++) {
                client = a;
            }
            printf("O cliente %s ganhou um kit da Localisa!", vetClients[client].name); 
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------- //

int find(int a, char params[]) { // 1: Clients , 2: Vehicles
    int exists = 0;

    switch (a) {

    case 1:
        for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0 && exists == 0; i++) {
            if (strcmp(vetClients[i].phone, params) == 0) {
                exists = 1;
            }
        }
        break;
    
    case 2:
        for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0 && exists == 0; i++) {
            if (strcmp(vetVehicles[i].plate, params) == 0) {
                exists = 1;
            }
        }
        break;
    }

    return exists;
} 

// --------------------------------------------------------------------------------------------------------------------- //

void saveFile(char a) {
    // c: clients, v: vehicles, l: leases

    FILE * file;

    switch (a) {
    case 'c':
        file = fopen("clientes.txt", "w");

        /* 
        File Data Structure:

        = -
        Code: x
        Name: x
        Address: x
        Phone: x
        - =
        */

        if (file != NULL) {
            for (int i = 0; strcmp(vetClients[i].code, "EOF") != 0; i++) {
                if (strcmp(vetClients[i].code, "") != 0) {
                fprintf(file, "= -\n");
                fprintf(file, "Code: %s\n", vetClients[i].code);
                fprintf(file, "Name: %s\n", vetClients[i].name);
                fprintf(file, "Address: %s\n", vetClients[i].address);
                fprintf(file, "Phone: %s\n", vetClients[i].phone);
                fprintf(file, "- =\n");
                }
            }
        }

        fclose(file);
        break;
    case 'v':
        file = fopen("veiculos.txt", "w");

        /*
        = -
        Code: x
        Desc: x
        Model: x
        Color: x
        Plate: x
        DailyValue: x
        OccupantsQtt: x
        Status: x
        -=
        */

        if (file != NULL) {
            for (int i = 0; strcmp(vetVehicles[i].code, "EOF") != 0; i++) {
                if (strcmp(vetVehicles[i].code, "") != 0) {
                fprintf(file, "= -\n");
                fprintf(file, "Code: %s\n", vetVehicles[i].code);
                fprintf(file, "Desc: %s\n", vetVehicles[i].desc);
                fprintf(file, "Model: %s\n", vetVehicles[i].model);
                fprintf(file, "Color: %s\n", vetVehicles[i].color);
                fprintf(file, "Plate: %s\n", vetVehicles[i].plate);
                fprintf(file, "DailyValue: %s\n", vetVehicles[i].daily_value);
                fprintf(file, "OccupantsQtt: %s\n", vetVehicles[i].occupants_quantity);
                fprintf(file, "Status: %s\n", vetVehicles[i].status);
                fprintf(file, "- =\n");
                }
            }
        }

        fclose(file);
        break;
    case 'l':
        file = fopen("locacoes.txt", "w");

        if (file != NULL) {
            for (int i = 0; strcmp(vetLeases[i].code, "EOF") != 0; i++) {
                if (strcmp(vetLeases[i].code, "") != 0) {
                fprintf(file, "= -\n");
                fprintf(file, "LeaseCode: %s\n", vetLeases[i].code); // Codigo Locação
                fprintf(file, "ClientCode: %s\n", vetLeases[i].client_code); // Codigo Cliente
                fprintf(file, "VehicleCode: %s\n", vetLeases[i].vehicle_code); // Codigo Veiculo
                fprintf(file, "LeaseDate: %s\n", vetLeases[i].lease_day); // Data de Retirada
                fprintf(file, "ReturnDate: %s\n", vetLeases[i].return_day);
                fprintf(file, "TotalValue: %s\n", vetLeases[i].total_value); // Data de Devolução
                fprintf(file, "LeaseDays: %s\n", vetLeases[i].days); // Quantidade de Dias Locados
                fprintf(file, "Insurance: %s\n", vetLeases[i].insurance); // Seguro
                fprintf(file, "- =\n");
                }
            }
        }
        fclose(file);
        break;
    }
}

void loadFile(char a) {
    int vetPos = 0; char dataType[50]; char dataResult[50]; FILE * file;

    switch (a) {

    case 'c':

    //

        file = fopen("clientes.txt", "r");

        if (file != NULL) {
            while (fscanf(file, "%s %[^\n]", &dataType, &dataResult) != EOF) {
                if (strcmp(dataType, "=") == 0) {
                    strcpy(vetClients[vetPos].code, "");
                    strcpy(vetClients[vetPos].name, "");
                    strcpy(vetClients[vetPos].address, "");
                    strcpy(vetClients[vetPos].phone, "");
                }
                if (strcmp(dataType, "Code:") == 0) {
                    strcpy(vetClients[vetPos].code, dataResult);
                }
                if (strcmp(dataType, "Name:") == 0) {
                    strcpy(vetClients[vetPos].name, dataResult);
                }
                if (strcmp(dataType, "Address:") == 0) {
                    strcpy(vetClients[vetPos].address, dataResult);
                }
                if (strcmp(dataType, "Phone:") == 0) {
                    strcpy(vetClients[vetPos].phone, dataResult);
                }
                if (strcmp(dataType, "-") == 0) {
                    vetPos++;
                }
            }
        }

        fclose(file);

        strcpy(vetClients[vetPos].code, "EOF");
    break;
    
    case 'v':
        file = fopen("veiculos.txt", "r");

        if (file != NULL) {
            while (fscanf(file, "%s %[^\n]", &dataType, &dataResult) != EOF) {
                if (strcmp(dataType, "=") == 0) {
                    strcpy(vetVehicles[vetPos].code, "");
                    strcpy(vetVehicles[vetPos].desc, "");
                    strcpy(vetVehicles[vetPos].model, "");
                    strcpy(vetVehicles[vetPos].color, "");
                    strcpy(vetVehicles[vetPos].plate, "");
                    strcpy(vetVehicles[vetPos].daily_value, "");
                    strcpy(vetVehicles[vetPos].occupants_quantity, "");
                    strcpy(vetVehicles[vetPos].status, "");
                }
                if (strcmp(dataType, "Code:") == 0) {
                    strcpy(vetVehicles[vetPos].code, dataResult);
                }
                if (strcmp(dataType, "Desc:") == 0) {
                    strcpy(vetVehicles[vetPos].desc, dataResult);
                }
                if (strcmp(dataType, "Model:") == 0) {
                    strcpy(vetVehicles[vetPos].model, dataResult);
                }
                if (strcmp(dataType, "Color:") == 0) {
                    strcpy(vetVehicles[vetPos].color, dataResult);
                }
                if (strcmp(dataType, "Plate:") == 0) {
                    strcpy(vetVehicles[vetPos].plate, dataResult);
                }
                if (strcmp(dataType, "DailyValue:") == 0) {
                    strcpy(vetVehicles[vetPos].daily_value, dataResult);
                }
                if (strcmp(dataType, "OccupantsQtt:") == 0) {
                    strcpy(vetVehicles[vetPos].occupants_quantity, dataResult);
                }
                if (strcmp(dataType, "Status:") == 0) {
                    strcpy(vetVehicles[vetPos].status, dataResult);
                }
                if (strcmp(dataType, "-") == 0) {
                    vetPos++;
                }
            }
        }

        fclose(file);

        strcpy(vetVehicles[vetPos].code, "EOF");
    break;
    
    case 'l':
        file = fopen("locacoes.txt", "r");

        if (file != NULL) {
            while (fscanf(file, "%s %[^\n]", &dataType, &dataResult) != EOF) {
                if (strcmp(dataType, "=") == 0) {
                    strcpy(vetLeases[vetPos].code, "");
                    strcpy(vetLeases[vetPos].client_code, "");
                    strcpy(vetLeases[vetPos].vehicle_code, "");
                    strcpy(vetLeases[vetPos].lease_day, "");
                    strcpy(vetLeases[vetPos].return_day, "");
                    strcpy(vetLeases[vetPos].days, "");
                    strcpy(vetLeases[vetPos].insurance, "");
                }
                if (strcmp(dataType, "LeaseCode:") == 0) {
                    strcpy(vetLeases[vetPos].code, dataResult);
                }
                if (strcmp(dataType, "ClientCode:") == 0) {
                    strcpy(vetLeases[vetPos].client_code, dataResult);
                }
                if (strcmp(dataType, "VehicleCode:") == 0) {
                    strcpy(vetLeases[vetPos].vehicle_code, dataResult);
                }
                if (strcmp(dataType, "LeaseDate:") == 0) {
                    strcpy(vetLeases[vetPos].lease_day, dataResult);
                }
                if (strcmp(dataType, "ReturnDate:") == 0) {
                    strcpy(vetLeases[vetPos].return_day, dataResult);
                }
                if (strcmp(dataType, "LeaseDays:") == 0) {
                    strcpy(vetLeases[vetPos].days, dataResult);
                }
                if (strcmp(dataType, "TotalValue:") == 0) {
                    strcpy(vetLeases[vetPos].total_value, dataResult);
                }
                if (strcmp(dataType, "Insurance:") == 0) {
                    strcpy(vetLeases[vetPos].insurance, dataResult);
                }
                if (strcmp(dataType, "-") == 0) {
                    vetPos++;
                }
            }
        }

        fclose(file);

        strcpy(vetLeases[vetPos].code, "EOF");
        break;
    }
}

// --------------------------------------------------------------------------------------------------------------------- //






