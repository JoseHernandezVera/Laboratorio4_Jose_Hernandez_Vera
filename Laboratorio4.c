#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Company 
{
    char nombre[50];
    int empleados[5];
};

// Ejercicio 2
void add_employee_data(struct Company *company, int year, int numEmpleados) 
{
    if (year >= 2018 && year <= 2022) 
	{
        company->empleados[year - 2018] = numEmpleados;
    } else {
        printf("Ano no valido. Debe estar en el rango de 2018 a 2022.\n");
    }
}

// Ejercicio 3
int find_total_employees(struct Company company, int year) 
{
    if (year >= 2018 && year <= 2022) 
	{
        return company.empleados[year - 2018];
    } else {
        printf("Ano no valido. Debe estar en el rango de 2018 a 2022.\n");
        return -1;
    }
}

// Ejercicio 4
void delete_employee_data(struct Company *company, int year) 
{
    if (year >= 2018 && year <= 2022) 
	{
        company->empleados[year - 2018] = 0;
    } else {
        printf("Ano no valido. Debe estar en el rango de 2018 a 2022.\n");
    }
}

// Ejercicio 5
float calculate_average_employees(struct Company company) 
{
    int totalEmployees = 0;
    for (int i = 0; i < 5; i++) 
	{
        totalEmployees += company.empleados[i];
    }
    return (float)totalEmployees / 5;
}

// Ejercicio 6
float general_average_employees(struct Company companies[], int numCompanies, int year) 
{
    int totalEmpleados = 0;
    for (int i = 0; i < numCompanies; i++) 
	{
        totalEmpleados += companies[i].empleados[year - 2018];
    }
    return (float)totalEmpleados / numCompanies;
}

int main() {
	
    int opcion;
    
    FILE *file = fopen("empresas.txt", "r");

    if (file == NULL) {
        perror("Error en abrir el .txt");
        return 1;
    }

    struct Company companies[10];
    int numCompanies = 0;

    while (numCompanies < 10 && fscanf(file, "%s %d %d %d %d %d",
            companies[numCompanies].nombre,
            &companies[numCompanies].empleados[0],
            &companies[numCompanies].empleados[1],
            &companies[numCompanies].empleados[2],
            &companies[numCompanies].empleados[3],
            &companies[numCompanies].empleados[4]) == 6) 
			{
        numCompanies++;
    }

    fclose(file);
    
    printf("INFORMACION DE LAS EMPRESAS: \n\n");
    
    for (int i = 0; i < numCompanies; i++) 
	{
       printf("Nombre de la empresa: %s\n", companies[i].nombre);
       printf("Cantidad de empleados por ano:\n");
       
       for (int year = 2018; year <= 2022; year++) 
	   {
        printf("%d: %d\n", year, companies[i].empleados[year - 2018]);
       }
       printf("\n");
    }
    
    printf("Que desea hacer: \n");

    do {
        printf("1. Agregar datos de empleados\n");
        printf("2. Encontrar cantidad de empleados para un ano\n");
        printf("3. Eliminar datos de empleados en todas las empresas en un ano\n");
        printf("4. Calcular promedio de empleados de una Compania\n");
        printf("5. Calcular promedio general de empleados de todas las Companias\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion) 
		{
            case 1:
                if (numCompanies < 10) 
				{
                    printf("Ingrese el nombre de la empresa: ");
                    scanf("%s", companies[numCompanies].nombre);
                    printf("Ingrese el ano (2018-2022): ");
                    int yearToAdd, employeesToAdd;
                    scanf("%d", &yearToAdd);
                    printf("Ingrese la cantidad de empleados: ");
                    scanf("%d", &employeesToAdd);
                    add_employee_data(&companies[numCompanies], yearToAdd, employeesToAdd);
                    numCompanies++;
                } else {
                    printf("No se pueden agregar mas companias.\n");
                }
                break;

            case 2:
                if (numCompanies > 0) 
				{
                    printf("Ingrese el ano (2018-2022): ");
                    int yearToFind, totalEmployees;
                    scanf("%d", &yearToFind);
                    for (int i = 0; i < numCompanies; i++) 
					{
                        totalEmployees = find_total_employees(companies[i], yearToFind);
                        if (totalEmployees != -1) 
						{
                            printf("Nombre de la empresa: %s, Cantidad de empleados en %d: %d\n", companies[i].nombre, yearToFind, totalEmployees);
                        }
                    }
                } else {
                    printf("No hay companias registradas.\n");
                }
                break;

            case 3:
                if (numCompanies > 0) 
				{
                    printf("Ingrese el ano (2018-2022): ");
                    int yearToDelete;
                    scanf("%d", &yearToDelete);
                    for (int i = 0; i < numCompanies; i++) 
					{
                        delete_employee_data(&companies[i], yearToDelete);
                    }
                } else {
                    printf("No hay companias registradas.\n");
                }
                break;

            case 4:
                if (numCompanies > 0) {
                    printf("Ingrese el nombre de la empresa: ");
                    char companyName[50];
                    scanf("%s", companyName);
                    for (int i = 0; i < numCompanies; i++) 
					{
                        if (strcmp(companies[i].nombre, companyName) == 0) 
						{
                            float avgEmployees = calculate_average_employees(companies[i]);
                            printf("Nombre de la empresa: %s, Promedio de empleados: %.2f\n", companies[i].nombre, avgEmployees);
                            break;
                        }
                        if (i == numCompanies - 1) 
						{
                            printf("La empresa no se encontro en la lista.\n");
                        }
                    }
                } else {
                    printf("No hay companias registradas.\n");
                }
                break;

            case 5:
                if (numCompanies > 0) 
				{
                    printf("Ingrese el ano (2018-2022): ");
                    int yearForGeneralAvg;
                    scanf("%d", &yearForGeneralAvg);
                    float generalAvg = general_average_employees(companies, numCompanies, yearForGeneralAvg);
                    printf("Promedio general de empleados en %d: %.2f\n", yearForGeneralAvg, generalAvg);
                } else {
                    printf("No hay companias registradas.\n");
                }
                break;

            case 6:
                break;

            default:
                printf("Opcion no valida. Por favor, seleccione una opcion valida.\n");
                break;
        }

    } while (opcion != 6);
    
    printf("\nFin del lab");

    return 0;
}