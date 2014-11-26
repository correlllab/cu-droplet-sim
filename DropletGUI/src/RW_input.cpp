/**
* \file	cu-droplet\DropletSimulator\DropletSimDemos\DropletGUI\src\RW_input.cpp
*
* \brief	Implements the input handling for the RenderWidget class.
*/
#include "RenderWidget.h"

// handle mouse movement
void RenderWidget::mouseMoveEvent ( QMouseEvent * event )
{
	if (event->buttons().testFlag(Qt::RightButton) && _mouseStatus.rightButtonHeldDown)
	{
		if (_camera.mode == 0)
		{
			_camera.rotHoriz = _mouseStatus.origHoriz + (event->x() - _mouseStatus.startX) / 2.0;
			_camera.rotVert = _mouseStatus.origVert - (event->y() - _mouseStatus.startY) / 2.0;
		} else if (_camera.mode == 1) {
			_camera.pan = _mouseStatus.origPan - (event->x() - _mouseStatus.startX) / 2.0;
			_camera.tilt =_mouseStatus.origTilt - (event->y() - _mouseStatus.startY) / 2.0;
		}
	}
	event->accept();
}

// handle mouse button pressed
void RenderWidget::mousePressEvent ( QMouseEvent * event )
{
	if (event->buttons().testFlag(Qt::MiddleButton)) {
		//no middle mouse button fuctionality;
	}

	if (event->buttons().testFlag(Qt::LeftButton))
	{
		_mouseStatus.leftButtonHeldDown = true;
		_mouseStatus.startX = event->x();
		_mouseStatus.startY = event->y();
		QPoint selectionPoint(_mouseStatus.startX,_mouseStatus.startY);
		mouseSelect(selectionPoint);
		event->accept();
	}

	if (event->buttons().testFlag(Qt::RightButton))
	{
		_mouseStatus.rightButtonHeldDown = true;
		_mouseStatus.startX = event->x();
		_mouseStatus.startY = event->y();
		_mouseStatus.origHoriz = _camera.rotHoriz;
		_mouseStatus.origVert = _camera.rotVert;
		_mouseStatus.origPan = _camera.pan;
		_mouseStatus.origTilt = _camera.tilt;
		setCursor(QCursor(Qt::BlankCursor));
		event->accept();
	}
}

// handle selection of droplet
void RenderWidget::mouseSelect (QPoint location)
{
	//QPoint toolTipLocation;
	QString toolTipText;
	QMatrix4x4 modelMatrix;

	// Window location

	setCursor(QCursor(Qt::CrossCursor));
	//toolTipLocation.setX(0.0f);
	//toolTipLocation.setY(0.0f);
	//toolTipText = QString("mouse = %1, %2").arg(_mouseStatus.startX).arg(_mouseStatus.startY);
	//toolTipText.append(QString("\ncamera = %1, %2, %3").arg(_camera.x).arg(_camera.y).arg(_camera.z));

	float width;
	float height;
	width = this->width();
	height = this->height();

	// NDE coordinates:
	QVector4D nds;
	nds.setX((2.0f * _mouseStatus.startX) / width - 1.0f);
	nds.setY(1.0f - (2.0f * _mouseStatus.startY) / height);
	nds.setZ(0.0f);
	nds.setW(0.0f);
	//toolTipText.append(QString("\nnds: %1, %2, %3").arg(nds.x()).arg(nds.y()).arg(nds.z()));
		
	// Clip coordinates:
	QVector4D clip;
	clip.setW(1.0);
	clip.setX(nds.x());
	clip.setY(nds.y());
	clip.setZ(nds.z());

	// near eye coordinates:
	QVector4D eye_near;
	eye_near = _camera.projectionMatrix.inverted() * clip;
	eye_near.operator/=(eye_near.w());

	// far eye coordinates:
	clip.setZ(1.0 * clip.w());
	QVector4D eye_far;
	eye_far = _camera.projectionMatrix.inverted() * clip;
	eye_far.operator/=(eye_far.w());

	modelMatrix = _camera.projectionMatrix;
	//toolTipText.append(QString("\n projection: \n %1 %2 %3 %4 \n %5 %6 %7 %8 \n %9 %10 %11 %12 \n %13 %14 %15 %16")
	//			.arg(modelMatrix.row(0).x()).arg(modelMatrix.row(0).y()).arg(modelMatrix.row(0).z()).arg(modelMatrix.row(0).w())
	//			.arg(modelMatrix.row(1).x()).arg(modelMatrix.row(1).y()).arg(modelMatrix.row(1).z()).arg(modelMatrix.row(1).w())
	//			.arg(modelMatrix.row(2).x()).arg(modelMatrix.row(2).y()).arg(modelMatrix.row(2).z()).arg(modelMatrix.row(2).w())
	//			.arg(modelMatrix.row(3).x()).arg(modelMatrix.row(3).y()).arg(modelMatrix.row(3).z()).arg(modelMatrix.row(3).w()));


	// show tool tip
	//toolTipText.append(QString("\n eye n: %1, %2, %3, %4 \n eye f: %5, %6, %7, %8")
	//	.arg(eye_near.x()).arg(eye_near.y()).arg(eye_near.z()).arg(eye_near.w())
	//	.arg(eye_far.x()).arg(eye_far.y()).arg(eye_far.z()).arg(eye_far.w()));

	//toolTipText.append(QString("\n r = %1").arg(_arena.dropletRadius));

	QVector3D click_ray;
	click_ray.setX(eye_far.x() - eye_near.x());
	click_ray.setY(eye_far.y() - eye_near.y());
	click_ray.setZ(eye_far.z() - eye_near.z());
	click_ray.normalize();
	//toolTipText.append(QString("\n ray = %1, %2, %3").arg(click_ray.x()).arg(click_ray.y()).arg(click_ray.z()));

	// show locations of droplets
	foreach(dropletStruct_t droplet,_renderState.dropletData)
	{
		glm::vec3 origin = glm::vec3( droplet.origin.x, droplet.origin.y, droplet.origin.z);

		glm::quat quaternion = glm::quat(droplet.quaternion.w,droplet.quaternion.x,
			droplet.quaternion.y,droplet.quaternion.z);

		glm::mat4 model =  glm::translate(glm::mat4(1.0f),origin);
		model = model * glm::mat4_cast(quaternion);
		model = glm::scale(model,glm::vec3(_arena.dropletRadius));
		model = glm::translate(model,glm::vec3(0,0,_arena.dropletOffset));

			
		QVector4D rowValues;
		for (int i = 0; i < 4; i++) 
		{
			rowValues.setX(model[i][0]);
			rowValues.setY(model[i][1]);
			rowValues.setZ(model[i][2]);
			rowValues.setW(model[i][3]);
			modelMatrix.setColumn(i,rowValues);
		}
		//toolTipText.append(QString("\n model: \n %1 %2 %3 %4 \n %5 %6 %7 %8 \n %9 %10 %11 %12 \n %13 %14 %15 %16")
		//		.arg(modelMatrix.row(0).x()).arg(modelMatrix.row(0).y()).arg(modelMatrix.row(0).z()).arg(modelMatrix.row(0).w())
		//		.arg(modelMatrix.row(1).x()).arg(modelMatrix.row(1).y()).arg(modelMatrix.row(1).z()).arg(modelMatrix.row(1).w())
		//		.arg(modelMatrix.row(2).x()).arg(modelMatrix.row(2).y()).arg(modelMatrix.row(2).z()).arg(modelMatrix.row(2).w())
		//		.arg(modelMatrix.row(3).x()).arg(modelMatrix.row(3).y()).arg(modelMatrix.row(3).z()).arg(modelMatrix.row(3).w()));

		QMatrix4x4 modelViewProj = _camera.viewMatrix * modelMatrix;
		QVector4D dropletOrigin;
		dropletOrigin.setX(0);
		dropletOrigin.setY(0);
		dropletOrigin.setZ(1.0);
		dropletOrigin.setW(1);
		//
		//toolTipText.append(QString("\norigin = %1, %2, %3").arg(dropletOrigin.x()).arg(dropletOrigin.y()).arg(dropletOrigin.z()));

		QVector4D dropletPosition = modelViewProj * dropletOrigin;
			
		//toolTipText.append(QString("\ndPos: %1, %2, %3, %4")
		//						.arg(dropletPosition.x())
		//						.arg(dropletPosition.y())
		//						.arg(dropletPosition.z())
		//						.arg(dropletPosition.w()));
			
		QVector3D u = QVector3D(dropletPosition.x() - eye_near.x(),
								dropletPosition.y() - eye_near.y(),
								dropletPosition.z() - eye_near.z());

		float projection = QVector3D::dotProduct(click_ray,u);
		//toolTipText.append(QString("\n p = %1").arg(projection));

		QVector3D toSphere;
		toSphere.setX(dropletPosition.x() - (eye_near.x() + projection * click_ray.x()));
		toSphere.setY(dropletPosition.y() - (eye_near.y() + projection * click_ray.y()));
		toSphere.setZ(dropletPosition.z() - (eye_near.z() + projection * click_ray.z()));
		//toolTipText.append(QString("\ngtoS = %1, %2, %3").arg(toSphere.x()).arg(toSphere.y()).arg(toSphere.z()));

		float distance = toSphere.length();
		//toolTipText.append(QString("\n dist = %1").arg(distance));

		if (distance <= _arena.dropletRadius) 
		{
			// TODO: keep only closest one to eye
			//toolTipText.append(QString("\nintersection"));
			toolTipText = QString("id = %1").arg(droplet.dropletID);
			unsigned int temp = droplet.color.r;
			droplet.color.r = droplet.color.b;
			droplet.color.b = droplet.color.g;
			droplet.color.g = temp;
			QToolTip::showText(location, toolTipText);
		}
		//else 
		//{
		//	toolTipText.append(QString("\nno intersection"));
		//}
		//QToolTip::showText(toolTipLocation,toolTipText);

	}
}

// handle releasing the mouse button
void RenderWidget::mouseReleaseEvent ( QMouseEvent * event )
{
	if (!event->buttons().testFlag(Qt::RightButton))
	{
		_mouseStatus.rightButtonHeldDown = false;
		setCursor(QCursor(Qt::ArrowCursor));
		event->accept();
	}

	if (!event->buttons().testFlag(Qt::LeftButton)) 
	{
		_mouseStatus.leftButtonHeldDown = false;
		event->accept();
	}
	
}

// event to handle scrolling with scroll wheel
void RenderWidget::wheelEvent(QWheelEvent *event)
{

	float numDegrees = event->delta() / 8;
	float numSteps = numDegrees / 15;

	if (event->orientation() == Qt::Vertical && _camera.mode == 0) {
#ifdef __APPLE__
		// compensate for apple's inverted scrolling
		_camera.radius += numSteps * 2.0;
#else
		// everyone else behaves correctly
		_camera.radius -= numSteps * 2.0;
#endif
	}
	event->accept();
}


void RenderWidget::keyPressEvent(QKeyEvent *event)
{
	if (!event->isAutoRepeat())
	{
		if(event->modifiers().testFlag(Qt::ControlModifier))
		{
			if(event->key() == Qt::Key_H)
			{
				_hud = !_hud;
			} 
			else if(event->key() == Qt::Key_R)
			{
				emit restart();
			} 
			else if(event->key() == Qt::Key_L)
			{
				_renderLock = true;
				assets.reloadAssets();
				setupRenderStructs();
				_renderLock = false;
			} 
			else if(event->key() == Qt::Key_B)
			{
				if (_renderDebug == 2)
				{
					_renderDebug = 0;
				} else {
					_renderDebug++;
				}
			}
		} else {
			if(event->key() == Qt::Key_Escape)
			{
				qApp->processEvents();
				close();
				makeCurrent();
				assets.clearAssets();
				doneCurrent();
			} else if(event->key() == Qt::Key_P)
			{
				emit togglePause();
			} else if(event->key() == Qt::Key_L)
			{
				emit toggleLimit();
			} else if(event->key() == Qt::Key_H)
			{
				_drawHelp = !_drawHelp;
			} else if(event->key() == Qt::Key_Q)
			{
				_keysDown.Q = true;
			} else if(event->key() == Qt::Key_W)
			{
				_keysDown.W = true;
			} else if(event->key() == Qt::Key_E)
			{
				_keysDown.E = true;
			} else if(event->key() == Qt::Key_A)
			{
				_keysDown.A = true;
			} else if(event->key() == Qt::Key_S)
			{
				_keysDown.S = true;
			} else if(event->key() == Qt::Key_D)
			{
				_keysDown.D = true;
			} else if(event->key() == Qt::Key_Plus)
			{
				_keysDown.Plus = true;
			} else if(event->key() == Qt::Key_Minus)
			{
				_keysDown.Minus = true;
			} else if(event->key() == Qt::Key_Space)
			{
				if (_camera.mode == 1)
				{
					_camera.mode = 0;
					_mouseStatus.origHoriz = _camera.rotHoriz;
					_mouseStatus.origVert = _camera.rotVert;

				} else
				{
					_camera.mode++;
					_mouseStatus.origPan = _camera.pan;
					_mouseStatus.origTilt = _camera.tilt;
				}
			} else if(event->key() == Qt::Key_Backslash)
			{
				makeCurrent();
				saveScreenShot(SCREENSHOT_WIDTH,SCREENSHOT_HEIGHT);
				assets.reloadAssets();
				setupRenderStructs();
				doneCurrent();
			}
		}
	}

	if(event->key() == Qt::Key_BracketRight)
	{
		if (_simRates.limitRate)
			emit decreaseRate();
	}
	if(event->key() == Qt::Key_BracketLeft)
	{
		if (_simRates.limitRate)
			emit increaseRate();
	}
}

void RenderWidget::keyReleaseEvent(QKeyEvent *event)
{
	if (!event->isAutoRepeat())
	{
		if(!event->modifiers().testFlag(Qt::ControlModifier))
		{
			if(event->key() == Qt::Key_Q)
			{
				_keysDown.Q = false;
			}
			if(event->key() == Qt::Key_W)
			{
				_keysDown.W = false;
			}
			if(event->key() == Qt::Key_E)
			{
				_keysDown.E = false;
			}
			if(event->key() == Qt::Key_A)
			{
				_keysDown.A = false;
			}
			if(event->key() == Qt::Key_S)
			{
				_keysDown.S = false;
			}
			if(event->key() == Qt::Key_D)
			{
				_keysDown.D = false;
			}
			if(event->key() == Qt::Key_Plus)
			{
				_keysDown.Plus = false;
			}
			if(event->key() == Qt::Key_Minus)
			{
				_keysDown.Minus = false;
			}
		}
	}
}

void RenderWidget::processInput(float timeSinceLastUpdate)
{

	float perFrame = timeSinceLastUpdate / 1000.0;
	if (_camera.mode == 0)
	{
		if ((_keysDown.Q || _keysDown.Minus) && (!_keysDown.E && !_keysDown.Plus))
		{
			_camera.radius += 100 * perFrame;
		} else if ((_keysDown.E || _keysDown.Plus) && (!_keysDown.Q && !_keysDown.Minus))
		{
			_camera.radius -= 100 * perFrame;
		}
		if (_keysDown.W && !_keysDown.S)
		{
			_camera.rotVert -= 45  * perFrame;
		} else if (_keysDown.S && !_keysDown.W)
		{
			_camera.rotVert += 45 * perFrame;
		}
		if (_keysDown.A && !_keysDown.D)
		{
			_camera.rotHoriz += 90 * perFrame;
		} else if (_keysDown.D && !_keysDown.A)
		{
			_camera.rotHoriz -= 90 * perFrame;
		}
	} else 	if (_camera.mode == 1)
	{
		if (_keysDown.Q && !_keysDown.E)
		{
            _camera.z -= 50 * perFrame;
		} else if (_keysDown.E && !_keysDown.Q)
		{
            _camera.z += 50 * perFrame;
		}
		if (_keysDown.W && !_keysDown.S)
		{
			_camera.x -= sin(_camera.pan * M_PI / 180) * 50 * perFrame;
			_camera.y -= -cos(_camera.pan * M_PI / 180) * 50 * perFrame;


		} else if (_keysDown.S && !_keysDown.W)
		{
			_camera.x += sin(_camera.pan * M_PI / 180) * 50 * perFrame;
			_camera.y += -cos(_camera.pan * M_PI / 180) * 50 * perFrame;
		}
        if (_keysDown.A && !_keysDown.D)
        {
            _camera.x -= cos(_camera.pan * M_PI / 180) * 50 * perFrame;
            _camera.y -= sinf(_camera.pan * M_PI / 180) * 50 * perFrame;


        } else if (_keysDown.D && !_keysDown.A)
        {
            _camera.x += cos(_camera.pan * M_PI / 180) * 50 * perFrame;
            _camera.y += sinf(_camera.pan * M_PI / 180) * 50 * perFrame;

        }
	}

}
