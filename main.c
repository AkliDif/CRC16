#include <stdio.h>
#include <math.h>


//fonctionne pour convertion d'un octet en binaire à entier à partir d'un tableau
int btoint (int*tab)
{
    int res=0;
    for (int i=0 ; i<8 ; i++)
        res+= tab[i]*pow(2,i);
    return res;
}


int initCRC (int nb_octets)
{
    int CRC = 0xFF, i, j;
    if (nb_octets == 1)
    {
        return 0xFF;
    }
    for (j = 0 ; j<nb_octets-1 ; j++)
    {
        for (i =0  ; i < 8 ; i++)
            CRC = CRC<<1;
        CRC += 0xFF;
    }

    return CRC;
}


int main (void)
{

    
    // faut adapter le CRC16 utiliser par rapport au nombres d'octet
    // 0xFF si 1 octet, 0xFFFF pour 2 octets etc
    int poly = 0xA001, CRC16 = 0, n=0, i, j, nb_octets, c, d;

    //On rentre le nombre de bits et on déclare un tableau de taille 8*nombre d'octet
    printf("Entrer le nombre d'octet\n");
    scanf("%d", &nb_octets);
    int size = 8*nb_octets;
    int data[size], data_temp[size];;
    int octet[8];
    //initialisation de CRC

    CRC16 = initCRC(nb_octets);

    //on saisi la data
    printf("Entrer de la data\n");
    for ( i = 0 ; i<size ; i++)
        scanf("%d", &data_temp[i]);
    
    //on inverse la data pour la lire de bon sens
    for ( i = 0 ; i<size ; i++)
        data[i] = data_temp[size-1-i];

    j = 0;
    while (j < nb_octets)
    {   
        //on récupére la data octet par octet
        for (i=0 ; i<8 ; i++)
            octet[i] = data[i+j*8];
        
        //convertir l'octet récupérer en entier pour faire le ou exclusif
        d = btoint(octet);

        CRC16 = CRC16^d;
        
        n = 0;
        while (n < 8)
        {
            //si CRC16 est paire on divise sur polynome
            if ((CRC16 & 1))
            {
                CRC16 = CRC16^poly;
            }
            //on décale d'un bit à droite
            CRC16 = CRC16 >>1;
            n++;
        }
        j++;
    }

    printf("%0x\n", CRC16);
    

    return 0;
}