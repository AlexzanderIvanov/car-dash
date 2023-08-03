#ifndef SECONDSCREENPRESENTER_HPP
#define SECONDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SecondScreenView;

class SecondScreenPresenter: public touchgfx::Presenter, public ModelListener {
public:
	SecondScreenPresenter(SecondScreenView &v);

	/**
	 * The activate function is called automatically when this screen is "switched in"
	 * (ie. made active). Initialization logic can be placed here.
	 */
	virtual void activate();

	/**
	 * The deactivate function is called automatically when this screen is "switched out"
	 * (ie. made inactive). Teardown functionality can be placed here.
	 */
	virtual void deactivate();

	virtual ~SecondScreenPresenter() {
	}
	;

	void setNewValue(uint8_t *newValue);

	void updateDisplaySettings(uint8_t *settings);

	void setManualErrorChangeScreen() {
		model->setManualErrorChangeScreen();
	}

	int getTpmsIdFr()
	{
		model->getTpmsIdFr();
	}

	int getTpmsIdRr()
	{
		model->getTpmsIdRr();
	}

	int getTpmsIdRl()
	{
		model->getTpmsIdRl();
	}

	int getTpmsIdFl()
	{
		model->getTpmsIdFl();
	}


	void setTpmsIdFr(int newTpmsIdFr)
	{
		model->setTpmsIdFr(newTpmsIdFr);
	}

	void setTpmsIdRr(int newTpmsIdRr)
	{
		model->setTpmsIdRr(newTpmsIdRr);
	}

	void setTpmsIdRl(int newTpmsIdRl)
	{
		model->setTpmsIdRl(newTpmsIdRl);
	}

	void setTpmsIdFl(int newTpmsIdFl)
	{
		model->setTpmsIdFl(newTpmsIdFl);
	}


private:
	SecondScreenPresenter();

	SecondScreenView &view;
};

#endif // SECONDSCREENPRESENTER_HPP
