## Data exposed through modbus registers

```
Additional notes:
- Register addresses start from 0
```

## Mappings by Register Type

#### INPUT_CONTACT

| Name                                  	|  Register Address 	|
|---------------------------------------	|-------------------	|
| Machine Status                        	| 0                 	|
| Emergency Stop Alarm                  	| 24                	|
| Paper Jam Alarm                         	| 25                	|

#### COIL

| Name                                  	|  Register Address 	|
|---------------------------------------	|-------------------	|
| Machine Running                       	| 0                 	|

#### INPUT_REGISTER

| Name                                  	|  Register Address 	|
|---------------------------------------	|-------------------	|
| Conveyor Max Prints Per Hour          	| 1                 	|
| Conveyor Min Prints Per Hour          	| 2                 	|
| Conveyor Current Print Per Hour       	| 3                 	|
| Feeder Capacity                       	| 4                 	|
| Feeder Percentage Full                	| 5                 	|
| Feeder Current Count                  	| 6                 	|
| Delivery Capacity                     	| 7                 	|
| Delivery Percentage Full              	| 8                 	|
| Delivery Current Count                	| 9                 	|
| Paint Station Cyan Capacity           	| 10                	|
| Paint Station Cyan Percentage Full    	| 11                	|
| Paint Station Cyan Current Count      	| 12                	|
| Paint Station Magenta Capacity        	| 13                	|
| Paint Station Magenta Percentage Full 	| 14                	|
| Paint Station Magenta Current Count   	| 15                	|
| Paint Station Yellow Capacity         	| 16                	|
| Paint Station Yellow Percentage Full  	| 17                	|
| Paint Station Yellow Current Count    	| 18                	|
| Paint Station Black Capacity          	| 19                	|
| Paint Station Black Percentage Full   	| 20                	|
| Paint Station Black Current Count     	| 21                	|

#### HOLDING_REGISTER

- Holding regsiter count actuators don't represent values,
just modify them (by adding/subtracting the values set to the actuator),
applies to 6, 9, 12, 15, 18, 21

| Name                                  	|  Register Address 	|
|---------------------------------------	|-------------------	|
| Default Values                        	| 22, 23, 24        	|
| Cyan Default Value                    	| 25                	|
| Magenta Default Value                 	| 26                	|
| Yellow Default Value                  	| 27                	|
| Black Default Value                   	| 28                	|
| Conveyor Prints Per Hour              	| 3                 	|
| Feeder Count                          	| 6                 	|
| Delivery Count                        	| 9                 	|
| Paint Station Cyan Count              	| 12                	|
| Paint Station Magenta Count           	| 15                	|
| Paint Station Yellow Count            	| 18                	|
| Paint Station Black Count             	| 21                	|

## Mappings by semantics

#### General

- Global machine controls and configuration

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Machine Status                        	| INPUT_CONTACT    	| 0                 	|
| Emergency Stop Alarm                  	| INPUT_CONTACT    	| 24                	|
| Paper Jam Alarm                         	| INPUT_CONTACT    	| 25                	|
| Machine Running                       	| COIL             	| 0                 	|
| Default Values                        	| HOLDING_REGISTER 	| 22, 23, 24        	|
| Cyan Default Value                    	| HOLDING_REGISTER 	| 25                	|
| Magenta Default Value                 	| HOLDING_REGISTER 	| 26                	|
| Yellow Default Value                  	| HOLDING_REGISTER 	| 27                	|
| Black Default Value                   	| HOLDING_REGISTER 	| 28                	|

#### Feeder 

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Feeder Capacity                       	| INPUT_REGISTER   	| 4                 	|
| Feeder Percentage Full                	| INPUT_REGISTER   	| 5                 	|
| Feeder Current Count                  	| INPUT_REGISTER   	| 6                 	|
| Feeder Count                          	| HOLDING_REGISTER 	| 6                 	|

#### Delivery

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Delivery Capacity                     	| INPUT_REGISTER   	| 7                 	|
| Delivery Percentage Full              	| INPUT_REGISTER   	| 8                 	|
| Delivery Current Count                	| INPUT_REGISTER   	| 9                 	|
| Delivery Count                        	| HOLDING_REGISTER 	| 9                 	|

#### Conveyor

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Conveyor Max Prints Per Hour          	| INPUT_REGISTER   	| 1                 	|
| Conveyor Min Prints Per Hour          	| INPUT_REGISTER   	| 2                 	|
| Conveyor Current Print Per Hour       	| INPUT_REGISTER   	| 3                 	|
| Conveyor Prints Per Hour              	| HOLDING_REGISTER 	| 3                 	|

#### Paint Station Cyan

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Paint Station Cyan Capacity           	| INPUT_REGISTER   	| 10                	|
| Paint Station Cyan Percentage Full    	| INPUT_REGISTER   	| 11                	|
| Paint Station Cyan Current Count      	| INPUT_REGISTER   	| 12                	|
| Paint Station Cyan Count              	| HOLDING_REGISTER 	| 12                	|

#### Paint Station Magenta

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Paint Station Magenta Capacity        	| INPUT_REGISTER   	| 13                	|
| Paint Station Magenta Percentage Full 	| INPUT_REGISTER   	| 14                	|
| Paint Station Magenta Current Count   	| INPUT_REGISTER   	| 15                	|
| Paint Station Magenta Count           	| HOLDING_REGISTER 	| 15                	|

#### Paint Station Yellow

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Paint Station Yellow Capacity         	| INPUT_REGISTER   	| 16                	|
| Paint Station Yellow Percentage Full  	| INPUT_REGISTER   	| 17                	|
| Paint Station Yellow Current Count    	| INPUT_REGISTER   	| 18                	|
| Paint Station Yellow Count            	| HOLDING_REGISTER 	| 18                	|

#### Paint Station Black

| Name                                  	| Register Type    	|  Register Address 	|
|---------------------------------------	|------------------	|-------------------	|
| Paint Station Black Capacity          	| INPUT_REGISTER   	| 19                	|
| Paint Station Black Percentage Full   	| INPUT_REGISTER   	| 20                	|
| Paint Station Black Current Count     	| INPUT_REGISTER   	| 21                	|
| Paint Station Black Count             	| HOLDING_REGISTER 	| 21                	|