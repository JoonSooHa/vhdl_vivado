# ----------------------------------------------------------------------------  
# 
#  Inipro Inc.          www.inipro.net
#
# ----------------------------------------------------------------------------
#
#     IO standard for Bank 26 Vcco supply is fixed at 1.8V
#     IO standard for Bank 65 Vcco supply is fixed at 1.2V
#
# ----------------------------------------------------------------------------
 
 
# ----------------------------------------------------------------------------
# High-speed expansion connector
# ---------------------------------------------------------------------------- 
# Bank 65
set_property PACKAGE_PIN F1   [get_ports { uart_rtl_0_txd }];  # pmod_c[2]  / "F1.DSI_D0_N"
set_property PACKAGE_PIN E4   [get_ports { uart_rtl_0_rxd }];  # pmod_c[3]  / "E4.DSI_D1_P"
set_property PACKAGE_PIN E3   [get_ports { dout_0         }];  # o_cts / pmod_c[4]  / "E3.DSI_D1_N"

set_property PACKAGE_PIN L2   [get_ports {clk_in1_0       }];  # "L2.CSI0_D3_P"

# ----------------------------------------------------------------------------
# Low-speed expansion connector
# ---------------------------------------------------------------------------- 
# Bank 26
set_property PACKAGE_PIN G6   [get_ports { reset_rtl_0 }];  # pmod_b[1]  / "G6.HD_GPIO_8"

# ----------------------------------------------------------------------------
#
# IOSTANDARD Constraints
#
# ---------------------------------------------------------------------------- 

# Set the bank voltage for IO Bank 26 to 1.8V
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 26]];

# Set the bank voltage for IO Bank 65 to 1.2V
set_property IOSTANDARD LVCMOS12 [get_ports -of_objects [get_iobanks 65]];
