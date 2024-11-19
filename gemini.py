import keyboard
import time

def Do():
	while keyboard.is_pressed('ctrl'):
		time.sleep(.01)

	keyboard.write('latex, nao fala nada')

keyboard.add_hotkey('ctrl+b', Do)
print('Pressione esc para sair.')
keyboard.wait('esc')