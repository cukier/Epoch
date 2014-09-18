/*
 * epoch.h
 *
 *  Created on: 08/06/2012
 *      Author: cuki
 */

#ifndef EPOCH_H_
#define EPOCH_H_

#include <stdio.h>
#include <stdlib.h>

#define umMinuto	60
#define umaHora		3600
#define umDia		86400
#define mesFev		2419200 //umDia * 28
#define mesFevX		2505600 //umDia * 28
#define umMes		2592000
#define	umMesX		2678400 //umMes + umDia
#define umAno		31536000 //365 * umDia
#define umAnoBi		126230400 //4 * umAno + umDia
//Epoch 1/jan/1970 00:00:00

int fromEpoch(double dataAtual) {
	unsigned short nrDias = 0;
	unsigned short cont = 0;
	unsigned short nrAnosBixsextos = 0;
	unsigned short anoAtual = 1970;
	unsigned short nrAnos = 0;
	unsigned short mes = 1;
	unsigned short dia = 1;
	unsigned char ehBisexto = 0;
	unsigned short horas = 0;
	unsigned short minutos = 0;
	unsigned short segundos = 0;

	for (cont = 1970; cont < (unsigned short) (dataAtual / umAno) + 1970; cont++) {
		if (((!(cont % 4)) && (cont % 100)) || (!(cont % 400)))
			nrAnosBixsextos++;
	}

	nrAnos = (dataAtual - umDia * nrAnosBixsextos) / umAno;
	anoAtual += nrAnos;
	nrDias = (dataAtual - ((double) nrAnos * umAno) - ((double) nrAnosBixsextos
			* umDia)) / umDia;
	ehBisexto
			= (((!(anoAtual % 4)) && (anoAtual % 100)) || (!(anoAtual % 400))) ? 1
					: 0;

	for (cont = 1; cont <= nrDias; ++cont) {
		++dia;
		if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes
				== 10 || mes == 12) {
			if (dia == 32) {
				++mes;
				dia = 1;
			}
		} else if (mes == 2) {
			if (ehBisexto) {
				if (dia == 30) {
					++mes;
					dia = 1;
				}
			} else if (dia == 29) {
				++mes;
				dia = 1;
			}
		} else {
			if (dia == 31) {
				mes++;
				dia = 1;
			}
		}
	}

	horas = (dataAtual - ((double) nrAnos * umAno) - ((double) nrAnosBixsextos
			* umDia) - ((double) nrDias * umDia)) / umaHora;
	minutos = (dataAtual - ((double) nrAnos * umAno)
			- ((double) nrAnosBixsextos * umDia) - ((double) nrDias * umDia)
			- ((double) horas * umaHora)) / umMinuto;
	segundos = (dataAtual - ((double) nrAnos * umAno)
			- ((double) nrAnosBixsextos * umDia) - ((double) nrDias * umDia)
			- ((double) horas * umaHora) - ((double) minutos * umMinuto));

	printf("%d/%d/%d %d:%d:%d", dia, mes, anoAtual, horas, minutos, segundos);

	return 0;

}

int toEpoch(unsigned short ano, unsigned char mes, unsigned char dia,
		unsigned char hora, unsigned char minuto, unsigned char segundo) {

	double epoch = 0;
	unsigned short cont = 0;
	unsigned short nrAnosBisextos = 0;
	unsigned char ehBisexto = 0;

	epoch = (double) segundo;
	epoch += (double) minuto * umMinuto;
	epoch += (double) hora * umaHora;
	epoch += (double) (dia - 1) * umDia;

	ehBisexto = (((!(ano % 4)) && (ano % 100)) || (!(ano % 400))) ? 1 : 0;

	for (cont = mes - 1; cont; --cont) {
		if (cont == 1 || cont == 3 || cont == 5 || cont == 7 || cont == 8
				|| cont == 10 || cont == 12)
			epoch += (double) umMesX;
		else if (cont == 2) {
			if (ehBisexto)
				epoch += (double) mesFevX;
			else
				epoch += (double) mesFev;
		} else
			epoch += (double) umMes;
	}

	for (cont = 1970; cont < ano; ++cont) {
		if (((!(cont % 4)) && (cont % 100)) || (!(cont % 400)))
			nrAnosBisextos++;
	}

	if (ano > 1970)
		epoch += (double) (ano - 1970) * umAno + (double) nrAnosBisextos
				* umDia;

	printf("\n%0.0f", epoch);

	return 0;
}
#endif /* EPOCH_H_ */
