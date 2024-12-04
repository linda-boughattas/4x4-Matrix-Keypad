# 4x4 Matrix Keypad 

This code demonstrates the implementation of a **4x4 matrix keypad** using an STM32F446RE microcontroller. It reads key presses using a scanning technique and identifies the pressed button.

## Key Code Components  

- **Initialization**:  
  - `HAL_Init()`, `SystemClock_Config()`, and `MX_GPIO_Init()` initialize the microcontroller's peripherals and GPIOs.  

- **Matrix Scanning**:  
  - The rows (PB1, PB13, PB14, PB15) are activated sequentially in the main loop.  
  - Delays are added between row activations for stability.  

- **Interrupts for Columns**:  
  - Columns (PA8, PB4, PB5, PB10) are configured as EXTI pins with pull-down resistors.  
  - The `HAL_GPIO_EXTI_Callback` function identifies the active column and determines the pressed button using a lookup table.  

## Hardware Requirements  

- **Microcontroller Board**: STM32F446RE  
- **Keypad**: 4x4 matrix keypad  
- **Connections**:  
  - Rows: PB1, PB13, PB14, PB15  
  - Columns: PA8, PB4, PB5, PB10  
- **Tools**: STM32CubeIDE or Keil uVision with CubeMX  

## Debugging  

Using Debug Mode, you can monitor the following variables in real-time:  
- `gLine`: The active row.  
- `gColumn`: The detected column.  
- `gKeyPressed`: The value of the pressed button.  

## Expected Results  

- Pressing a button updates `gKeyPressed` to show its value.  
- `gLine` and `gColumn` display the row and column coordinates of the press.  

## Images  

### Pin Configuration 

<p align="center">
  <img src="https://github.com/user-attachments/assets/bcaaa544-278d-4dfb-85b5-6b1f044bb76e" width="500">
</p>
