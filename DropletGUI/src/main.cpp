/**
 * \file	cu-droplet\DropletSimulator\DropletSimDemos\DropletGUI\src\main.cpp
 *
 * \brief	Implements the main function.
 */
#include <iostream>
#include <fstream>
#include <QApplication>
#include "MainWindow.h"

//! [0]
int main(int argc, char **argv)
{

	// redirect cout
	std::ofstream out("fbo.log");
	std::cout.rdbuf(out.rdbuf());
	std::cout<<"frame buffer object debug log"<<std::endl;

	// initialize the QApplication object	
	QApplication a(argc, argv);

	// create the main window
	MainWindow mw;
	QDesktopWidget * desktop = QApplication::desktop();
	QSize size = mw.sizeHint();
	int w = size.width();
	int h = size.height();
	int screen_width = desktop->width();
	int screen_height = desktop->height();

	// TODO : Start app in the top left corner of the screen. Account for toolbar area.
//	mw.setGeometry(screen_width/2 - w/2, screen_height/2 - h/2, w, h);
	mw.setGeometry(w/8, h/8, w, h);

	// show the main window
	mw.show();

	// start the main program execution loop
	int result = a.exec();

	// cleanup
	return result;
}
//! [0]
