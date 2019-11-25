### Data exposed through modbus registers

Additional notes:

- Register addresses start from 0
- Holding regsiter count actuators don't represent values,
just modify them (by adding/subtracting the values set to the actuator)

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Machine Status                        	| INPUT_CONTACT    	| 0                 	|
| Emergency Stop Alarm                  	| INPUT_CONTACT    	| 24                	|
|  Paper Jam Alarm                      	| INPUT_CONTACT    	| 25                	|
| Machine Running                       	| COIL             	| 0                 	|
| Conveyor Max Prints Per Hour          	| INPUT_REGISTER   	| 1                 	|
| Conveyor Min Prints Per Hour          	| INPUT_REGISTER   	| 2                 	|
| Conveyor Current Print Per Hour       	| INPUT_REGISTER   	| 3                 	|
| Feeder Capacity                       	| INPUT_REGISTER   	| 4                 	|
| Feeder Percentage Full                	| INPUT_REGISTER   	| 5                 	|
| Feeder Current Count                  	| INPUT_REGISTER   	| 6                 	|
| Delivery Capacity                     	| INPUT_REGISTER   	| 7                 	|
| Delivery Percentage Full              	| INPUT_REGISTER   	| 8                 	|
| Delivery Current Count                	| INPUT_REGISTER   	| 9                 	|
| Paint Station Cyan Capacity           	| INPUT_REGISTER   	| 10                	|
| Paint Station Cyan Percentage Full    	| INPUT_REGISTER   	| 11                	|
| Paint Station Cyan Current Count      	| INPUT_REGISTER   	| 12                	|
| Paint Station Magenta Capacity        	| INPUT_REGISTER   	| 13                	|
| Paint Station Magenta Percentage Full 	| INPUT_REGISTER   	| 14                	|
| Paint Station Magenta Current Count   	| INPUT_REGISTER   	| 15                	|
| Paint Station Yellow Capacity         	| INPUT_REGISTER   	| 16                	|
| Paint Station Yellow Percentage Full  	| INPUT_REGISTER   	| 17                	|
| Paint Station Yellow Current Count    	| INPUT_REGISTER   	| 18                	|
| Paint Station Black Capacity          	| INPUT_REGISTER   	| 19                	|
| Paint Station Black Percentage Full   	| INPUT_REGISTER   	| 20                	|
| Paint Station Black Current Count     	| INPUT_REGISTER   	| 21                	|
| Conveyor Prints Per Hour              	| HOLDING_REGISTER 	| 3                 	|
| Feeder Count                          	| HOLDING_REGISTER 	| 6                 	|
| Delivery Count                        	| HOLDING_REGISTER 	| 9                 	|
| Paint Station Cyan Count              	| HOLDING_REGISTER 	| 12                	|
| Paint Station Magenta Count           	| HOLDING_REGISTER 	| 15                	|
| Paint Station Yellow Count            	| HOLDING_REGISTER 	| 18                	|
| Paint Station Black Count             	| HOLDING_REGISTER 	| 21                	|
| Default Values                        	| HOLDING_REGISTER 	| 22, 23, 24        	|
| Cyan Default Value                    	| HOLDING_REGISTER 	| 25                	|
| Magenta Default Value                 	| HOLDING_REGISTER 	| 26                	|
| Yellow Default Value                  	| HOLDING_REGISTER 	| 27                	|
| Black Default Value                   	| HOLDING_REGISTER 	| 28                	|