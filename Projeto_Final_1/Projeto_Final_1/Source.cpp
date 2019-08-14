/*
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <windows.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	vector<int> compression_params; //vector que guarda os parametros para salvar a imagem
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //formato da imagem (jpg)
	compression_params.push_back(98); //squalidade da imagem (0 a 100)

	long long int tempo1, tempo2, diftempo; //variaveis que vão guardar o tempo para fazer a atualização da imagem de referencia
	int cont = 0;

	VideoCapture cap; //cria a variavel para abrir a camera (web cam)
	cap.open(1); // abre a webcam(0), se tiver outras cameras muda-se o numero(1,2,3...)
	Sleep(1000); // pausa o código durante 1 segundo para a camera estabilizar

	if (!cap.open(1)) { // verifica se a camera abriu, se não envia a mensagem de erro e termina o programa
		cout << "ERRO\n";
		system("PAUSE");
		return 0;
	}

	for (;;) // loop infinito
	{
		tempo1 = GetTickCount(); //pega o tempo de execuçao do programa até aqui

		Mat frame; //cria uma matriz
		cap >> frame; // captura uma matriz(imagem) através da variavel da camera
		if (frame.empty()) break; // se não capturar nenhum frame encerra o programa

		Mat img(650, 600, CV_16UC3, Scalar(0, 50000, 50000)); //cria uma imagem ( 3 channels, 16 bit image depth, 650 high, 600 wide, (0, 50000, 50000) assigned for Blue, Green and Red plane respectively. )
		Mat comp1(650, 600, CV_16UC3, Scalar(0, 50000, 50000));
		Mat comp2(650, 600, CV_16UC3, Scalar(0, 50000, 50000));
		Mat comp3(650, 600, CV_16UC3, Scalar(0, 50000, 50000));

		if (img.empty()) { //se não criar a imagem encerra o programa
			cout << "ERROR : Image cannot be loaded..!!" << endl;
			return -1;
		}
		img = frame; // atribue o que foi capturado pela webcam na imagem criada

		imwrite("Reference.jpg", img, compression_params); //salva a imagem no computador (nome_do_arquivo,imagem,parametros de compressão definidos no comeco do codigo) 
														   //imshow("Reference", img); //mostra a imagem(img) na janela que voce abriu

		for (;;) { //loop infinito

			tempo2 = GetTickCount(); //pega o tempo de execuçao do programa até aqui

			Mat frame2;
			cap >> frame2;
			if (frame2.empty()) break; // end of video stream

			Mat img2(650, 600, CV_16UC3, Scalar(0, 50000, 50000)); //create an image ( 3 channels, 16 bit image depth, 650 high, 600 wide, (0, 50000, 50000) assigned for Blue, Green and Red plane respectively. )

			if (img2.empty()) //check whether the image is loaded or not
			{
				cout << "ERROR : Image cannot be loaded..!!" << endl;
				system("PAUSE");
				return -1;
			}
			img2 = frame2;

			imwrite("Image.jpg", img2, compression_params);

			Mat ref = imread("Reference.jpg", CV_LOAD_IMAGE_UNCHANGED);
			Mat img = imread("Image.jpg", CV_LOAD_IMAGE_UNCHANGED);

			Mat dif; //cria uma matriz
			absdiff(ref, img, dif);// salva a diferença de ref e img em diffImage

			Mat foregroundMask = Mat::zeros(dif.rows, dif.cols, CV_8UC1); //cria uma matriz e preenche ela com zeros

			float threshold = 250.0f; // valor de referencia para a variação
			float dist;
			long long int valor_dif = 0; //valor numérico da diferença

			for (int j = 0; j < dif.rows; ++j) //percorre a imagem(matriz) dif 
				for (int i = 0; i < dif.cols; ++i)
				{
					Vec3b pix = dif.at<Vec3b>(j, i); // acessa os valores(valor do pixel) da imagem nos 3 canais

					dist = (pix[0] * pix[0] + pix[1] * pix[1] + pix[2] * pix[2]); // operação entre os valores dos canais 1, 2 (RGB)
					dist = sqrt(dist); // tira a raiz quadrada do valor calculado acima

					if (dist > threshold) // se houvel variação maior que a referencia
					{
						foregroundMask.at<unsigned char>(j, i) = 255; // muda a cor do pixel para branco(255)
						valor_dif++; //incrementa a variavel para pegar o valor numerico da variação

					}
				}

			//imwrite("Dif.jpg", dif, compression_params);

			//imwrite("Dif2.jpg", foregroundMask, compression_params);

			diftempo = tempo2 - tempo1;
			if (diftempo >= 10000) {
				tempo1 = tempo2 = 0;
				cout << "ok\n";
				break;
			}

			cout << valor_dif << endl; // mostra o valor da variação

			if (valor_dif > 0) {
				cont++;
			}
			else cont = 0;

			if (cont == 1) {
				comp1 = frame2;
			}
			if (cont == 2) {
				comp2 = frame2;
			}
			if (cont >= 3) {

				comp3 = frame2;

				imwrite("Comp1.jpg", comp1, compression_params);
				imwrite("Comp2.jpg", comp2, compression_params);
				imwrite("Comp3.jpg", comp3, compression_params);

				system("D:\\PiscinaSegura\\Envia_Email_Imagem1.exe");
				return 0;
			}
			Sleep(500);

		}
	}

	return 0;
}
*/


#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <windows.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	vector<int> compression_params; //vetor que guarda os parâmetros de compressão para salvar a imagem
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //formato, técnina de compressão da imagem (jpg)
	compression_params.push_back(98); //qualidade da imagem (0 a 100)

	long long int tempo1, tempo2, diftempo; //variaveis que vão guardar o tempo para fazer a atualização da imagem de referencia
	int cont = 0;

	VideoCapture cap; //cria a variável para abrir a câmera (webcam)
	cap.open(0); //abre a webcam(0), se tiver outras câmeras muda-se o numero(1,2,3...)
	Sleep(1000); //pausa o código durante 1 segundo para a câmera estabilizar

	if (!cap.isOpened()) { //verifica se a câmera abriu, se não envia a mensagem de erro e termina o programa
		system("D:\\PiscinaSegura\\Envia_Email_Erro.exe");
		return 0;
	}

	for (;;) //loop infinito
	{
		tempo1 = GetTickCount(); //pega o tempo de execução do programa até aqui

		Mat frame; //cria uma matriz
		cap >> frame; //captura uma matriz(imagem) através da variável da câmera
		if (frame.empty()) break; //se não capturar nenhum frame encerra o programa

		Mat img(650, 600, CV_16UC3, Scalar(0, 50000, 50000)); //cria uma imagem (3 canais 16 bits de profundidade, 650 pixels altura, 600 pixels largura, (0, 50000, 50000) atribuídos para, Azul, Verde e Vermelho, respectivamente)
		Mat img2(650, 600, CV_16UC3, Scalar(0, 50000, 50000)); //cria uma imagem (3 canais 16 bits de profundidade, 650 pixels altura, 600 pixels largura, (0, 50000, 50000) atribuídos para, Azul, Verde e Vermelho, respectivamente)
		Mat comp1(650, 600, CV_16UC3, Scalar(0, 50000, 50000));//cria uma imagem (3 canais 16 bits de profundidade, 650 pixels altura, 600 pixels largura, (0, 50000, 50000) atribuídos para, Azul, Verde e Vermelho, respectivamente)
		Mat comp2(650, 600, CV_16UC3, Scalar(0, 50000, 50000));//cria uma imagem (3 canais 16 bits de profundidade, 650 pixels altura, 600 pixels largura, (0, 50000, 50000) atribuídos para, Azul, Verde e Vermelho, respectivamente)
		Mat comp3(650, 600, CV_16UC3, Scalar(0, 50000, 50000));//cria uma imagem (3 canais 16 bits de profundidade, 650 pixels altura, 600 pixels largura, (0, 50000, 50000) atribuídos para, Azul, Verde e Vermelho, respectivamente)

		if (img.empty()) { //se não criar a imagem encerra o programa
			cout << "ERROR : Image cannot be loaded..!!" << endl;
			system("PAUSE");
			return -1;
		}

		img = frame; //atribui o que foi capturado pela webcam na imagem criada

		imwrite("Reference.jpg", img, compression_params); //salva a imagem de referência no computador (nome_do_arquivo,imagem,parâmetros de compressão definidos no começo do código) 

		for (;;) { //loop infinito

			tempo2 = GetTickCount(); //pega o tempo de execuçao do programa até aqui

			Mat frame2;//cria uma matriz
			cap >> frame2;//captura uma matriz(imagem) através da variável da câmera
			if (frame2.empty()) break; //se não capturar nenhum frame encerra o programa

			if (img2.empty()) //se não criar a imagem encerra o programa
			{
				cout << "ERROR : Image cannot be loaded..!!" << endl;
				system("PAUSE");
				return -1;
			}

			img2 = frame2; //atribui o que foi capturado pela webcam na imagem criada

			imwrite("Image.jpg", img2, compression_params);//salva a nova imagem no computador (nome_do_arquivo,imagem,parâmetros de compressão definidos no começo do código) 

			Mat ref = imread("Reference.jpg", CV_LOAD_IMAGE_UNCHANGED);//lê a iimagem de referência e salva em ref
			Mat img = imread("Image.jpg", CV_LOAD_IMAGE_UNCHANGED);//lê a nova imagem e salva em img

			Mat dif; //cria uma matriz para armazenar a diferença
			absdiff(ref, img, dif);//salva a diferença de ref e img em dif

			float threshold = 250.0f;//valor de referência para a variação (Empirico)
			float dist; //valor do módulo dos canais RGB
			long long int valor_dif = 0;//valor numérico da diferença

			for (int j = 0; j < dif.rows; ++j)//percorre a imagem(matriz) dif 
				for (int i = 0; i < dif.cols; ++i)
				{
					Vec3b pix = dif.at<Vec3b>(j, i);//acessa os valores(valor do pixel) da imagem nos 3 canais

					dist = (pix[0] * pix[0] + pix[1] * pix[1] + pix[2] * pix[2]); //operação entre os valores dos canais 1, 2 e 3 (RGB)
					dist = sqrt(dist); //tira a raiz quadrada do valor calculado acima (módulo)

					if (dist > threshold) //se houve uma variação maior que a referência
					{
						valor_dif++;//incrementa a variável para pegar o valor numérico da variação
					}
				}

			diftempo = tempo2 - tempo1;
			if (diftempo >= 10000) {
				tempo1 = tempo2 = 0;
				cout << "Imagem de referencia atualizada!\n";
				break;
			}

			cout << valor_dif << endl; //mostra o valor da variação

			if (valor_dif > 0)
			{
				cont++;
			}
			else cont = 0;

			if (cont == 1)
			{
				comp1 = frame2;
			}
			if (cont == 2)
			{
				comp2 = frame2;
			}
			if (cont >= 3)
			{
				comp3 = frame2;

				imwrite("Comp1.jpg", comp1, compression_params);
				imwrite("Comp2.jpg", comp2, compression_params);
				imwrite("Comp3.jpg", comp3, compression_params);

				system("D:\\PiscinaSegura\\AlarmeArduino.exe");
				system("D:\\PiscinaSegura\\Envia_Email_Imagem1.exe");

				return 0;
			}
			Sleep(200);
		}
	}
	system("PAUSE");

	return 0;
}