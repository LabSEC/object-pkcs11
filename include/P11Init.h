#ifndef P11INIT_H
#define P11INIT_H

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
class P11Init
{
protected:
	/*!
	* Simple state enumerator, dead r alive!
	*/
	enum state
	{
		DEAD = 0,
		ALIVE = 1
	};

	P11Init::state _currentState;

	/*!
	* Sets _currentState to DEAD
	*/
	void kill()
	{
		this->_currentState = P11Init::DEAD;
	}

	/*!
	* Sets _currentSate to ALIVE
	*/
	void ress()
	{
		this->_currentState = P11Init::ALIVE;
	}
public:
	/*!
	* Default Constructor, initializes as DEAD.
	*/
	P11Init(P11Init::state st = P11Init::DEAD) : _currentState(st){};

	/*!
	* Default destructor
	*/
	virtual ~P11Init() throw(){};

	/*!
	* Returns the current state of the class.
	* @return _currentState
	*/
	P11Init::state getState()
	{
		return this->_currentState;
	};

	/*!
	* Returns true is instance is ALIVE.
	* @return true if is ALIVE
	*/
	bool isAlive()
	{
		return _currentState;
	};
};
#endif /*P11INIT_H*/
