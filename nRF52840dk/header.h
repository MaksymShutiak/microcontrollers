#define GPIO_PIN_CNF_DIR_Input (0UL) /*!< Configure pin as an input pin. */
#define GPIO_PIN_CNF_DIR_Output (1UL) /*!< Configure pin as an output pin. */
#define GPIO_PIN_CNF_INPUT_Connect (0UL) /*!< Connect input pin. */
#define GPIO_PIN_CNF_INPUT_Disconnect (1UL) /*!< Disconnect input pin. */
#define GPIO_PIN_CNF_PULL_Disabled (0x00UL) /*!< No pull. */
#define GPIO_PIN_CNF_PULL_Pulldown (0x01UL) /*!< Pulldown on pin. */
#define GPIO_PIN_CNF_PULL_Pullup (0x03UL) /*!< Pullup on pin. */
#define GPIO_PIN_CNF_SENSE_Disabled (0x00UL) /*!< Disabled. */
#define GPIO_PIN_CNF_DRIVE_S0S1 (0x00UL) /*!< Standard '0', Standard '1'. */
#define GPIO_PIN_CNF_DIR_Pos (0UL) /*!< Position of DIR field. */
#define GPIO_PIN_CNF_DRIVE_Pos (8UL) /*!< Position of DRIVE field. */
#define GPIO_PIN_CNF_INPUT_Pos (1UL) /*!< Position of INPUT field. */
#define GPIO_PIN_CNF_PULL_Pos (2UL) /*!< Position of PULL field. */
#define GPIO_PIN_CNF_SENSE_Pos (16UL) /*!< Position of SENSE field. */

enum 
{
    NRF_GPIO_PIN_DIR_INPUT  = GPIO_PIN_CNF_DIR_Input, ///< Input.
    NRF_GPIO_PIN_DIR_OUTPUT = GPIO_PIN_CNF_DIR_Output ///< Output.
};

enum
{
    NRF_GPIO_PIN_INPUT_CONNECT    = GPIO_PIN_CNF_INPUT_Connect,   ///< Connect input buffer.
    NRF_GPIO_PIN_INPUT_DISCONNECT = GPIO_PIN_CNF_INPUT_Disconnect ///< Disconnect input buffer.
};

enum
{
    NRF_GPIO_PIN_NOPULL   = GPIO_PIN_CNF_PULL_Disabled, ///<  Pin pull-up resistor disabled.
    NRF_GPIO_PIN_PULLDOWN = GPIO_PIN_CNF_PULL_Pulldown, ///<  Pin pull-down resistor enabled.
    NRF_GPIO_PIN_PULLUP   = GPIO_PIN_CNF_PULL_Pullup,   ///<  Pin pull-up resistor enabled.
};



