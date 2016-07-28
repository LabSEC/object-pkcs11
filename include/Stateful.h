#ifndef STATEFUL_H
#define STATEFUL_H

namespace raiki {
/*!
 * @brief <b>Initializable abstract class</b><br>
 *
 * This is a utility classe for initialization control.
 * It is also possible to use this class for pre-conditioning
 * function implementations when developing applications (DbC).
 * 
 * @see http://sunday-lab.blogspot.com.br/2006/04/pre-condition-and-post-condition-in-c.html
 *
 * @author Lucas Pandolfo Perin
 */
class Stateful
{
protected:
	/*!
	* Simple state enumerator, ENABLED or DISABLED!
	*/
	enum state
	{
		DISABLED = 0,
		ENABLED = 1
	};

	Stateful::state _currentState;

	/*!
	* Sets _currentState to DISABLED
	*/
	void disable()
	{
		this->_currentState = Stateful::DISABLED;
	}

	/*!
	* Sets _currentSate to ALIVE
	*/
	void enable()
	{
		this->_currentState = Stateful::ENABLED;
	}
public:
	/*!
	* Default Constructor, initializes as DEAD.
	*/
	Stateful(Stateful::state st = Stateful::DISABLED) : _currentState(st){};

	/*!
	* Default destructor
	*/
	virtual ~Stateful() throw(){};

	/*!
	* Returns the current state of the class.
	* @return _currentState
	*/
	Stateful::state getState()
	{
		return _currentState;
	};

	/*!
	* Returns true is instance is ALIVE.
	* @return true if is ALIVE
	*/
	bool isEnabled()
	{
		return _currentState == Stateful::ENABLED;
	};

	/*!
	* Returns true is instance is DEAD.
	* @return true if is DEAD
	*/
	bool isDisabled()
	{
		return _currentState == Stateful::DISABLED;
	};
};
}/*END NAMESPACE*/
#endif /*STATEFUL_H*/
