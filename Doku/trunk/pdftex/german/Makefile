LISTE1 = ../GNU/RLvtot.eps ../GNU/RLvlow.eps ../GNU/RLvhigh.eps ../GNU/RHv.eps ../GNU/Mega8res.eps
LISTE1 += ../GNU/Mega8cap.eps ../GNU/Mega168cap.eps ../GNU/Mega168cap_opt.eps ../GNU/Mega168all.eps 
LISTE1 += ../GNU/ComparatorAdjust.eps ../GNU/Mega328all.eps ../GNU/Mega1284.eps ../GNU/SelfTref.eps ../GNU/MegaAuto.eps
LISTE1 += ../GNU/m168res_all.eps ../GNU/induct328p.eps ../GNU/Cesr.eps ../GNU/Cesr2.eps ../GNU/res_esr.eps
LISTE1 += ../GNU/Elco_esr.eps ../GNU/frequency-ppm.eps
LISTE1 += ../GNU/Cap_FC_data.eps ../GNU/Cap_FR_data.eps ../GNU/Cap_FC_FR_data.eps
LISTE1 += ../FIG/Messung.eps ../FIG/port.eps ../FIG/ResistormessH1.eps ../FIG/ResistormessH2.eps ../FIG/ResistormessL1.eps
LISTE1 += ../FIG/ResistormessL2.eps ../FIG/terminal.eps
LISTE1 += ../FIG/Comparat.eps ../FIG/Test2.eps ../FIG/Test7.eps ../FIG/Test8.eps ../FIG/Bigcap.eps
LISTE1 += ../FIG/PNPcc.eps ../FIG/PNPce.eps ../FIG/NPNce.eps ../FIG/ttester.eps ../FIG/t644tester.eps ../FIG/relay_addon.eps
LISTE1 += ../FIG/diode_addon.eps ../FIG/zener_exp.eps ../FIG/Frequency_addon.eps
LISTE1 += ../FIG/Inductance.eps ../FIG/JFETcd.eps ../FIG/Cap_equiv.eps ../FIG/Cap_esr.eps ../FIG/Cap_esr2.eps ../FIG/Cap_esr2_timing.eps
LISTE1 += ../FIG/CheckSemi1.eps ../FIG/CheckSemi2.eps ../FIG/CheckSemi3.eps
LISTE1 += ../FIG/rotary_extension.eps ../FIG/rotary_encoder.eps	../FIG/rotary_bouncing.eps
LISTE1 += ../FIG/Fish8840.eps ../FIG/ST7565lcd.eps ../FIG/ST7920interface.eps ../FIG/ST7108serial164.eps

LISTE2 = ../FIG/BJT_AD161.eps ../FIG/BJT_AD162.eps ../FIG/BJT_BC639.eps ../FIG/BJT_BC640.eps ../FIG/BJT_BU508D.eps
LISTE2 += ../FIG/BJT_BC516.eps ../FIG/BJT_BC517.eps ../FIG/BJT_BDV64.eps ../FIG/BJT_BDV65.eps
LISTE2 += ../FIG/JFET_BF245.eps ../FIG/JFET_J175.eps ../FIG/MOS_BSS169.eps ../FIG/MOS_BUZ71.eps ../FIG/MOS_IRF5305.eps
LISTE2 += ../FIG/GPS_UP501.eps ../FIG/GPS_GNS701.eps

all: ttester.pdf ttinfo.pdf
	
../GNU/RLvtot.eps: ../GNU/RLvtot.gnu
	gnuplot $<
../GNU/RLvlow.eps: ../GNU/RLvlow.gnu
	gnuplot $<
../GNU/RLvhigh.eps: ../GNU/RLvhigh.gnu
	gnuplot $<
../GNU/RHv.eps: ../GNU/RHv.gnu
	gnuplot $<
../GNU/Mega8res.eps: ../GNU/rmess.gnu ../GNU/rmess.dat
	gnuplot ../GNU/rmess.gnu
../GNU/Mega8cap.eps: ../GNU/capmess8.gnu ../GNU/capmess8.dat ../GNU/capmessorig.dat
	gnuplot ../GNU/capmess8.gnu
../GNU/Mega168cap.eps: ../GNU/capmess168.gnu ../GNU/capmess168.dat
	gnuplot ../GNU/capmess168.gnu
../GNU/Mega168cap_opt.eps: ../GNU/capmessopt168.gnu ../GNU/capmess168-3.dat
	gnuplot ../GNU/capmessopt168.gnu
../GNU/Mega168all.eps: ../GNU/capmess168all.gnu ../GNU/capmess168-all.dat ../GNU/capmess168-autocal.dat
	gnuplot ../GNU/capmess168all.gnu
../GNU/Mega328all.eps: ../GNU/capmess328all.gnu ../GNU/capmess328-all.dat ../GNU/capmess328-autocal.dat
	gnuplot ../GNU/capmess328all.gnu
../GNU/Mega1284.eps: ../GNU/capmess1284.gnu ../GNU/capmess1284.dat
	gnuplot ../GNU/capmess1284.gnu
../GNU/ComparatorAdjust.eps: ../GNU/comparator_diff.gnu ../GNU/comparator_cap.dat
	gnuplot ../GNU/comparator_diff.gnu
../GNU/SelfTref.eps: ../GNU/selftest.gnu ../GNU/selftest.dat
	gnuplot ../GNU/selftest.gnu
../GNU/MegaAuto.eps: ../GNU/capmessAUTO.gnu ../GNU/capmessAUTO.dat
	gnuplot ../GNU/capmessAUTO.gnu
../GNU/m168res_all.eps: ../GNU/rmess_all.gnu ../GNU/rmess-all.dat ../GNU/rmess-autocal.dat
	gnuplot ../GNU/rmess_all.gnu
../GNU/induct328p.eps: ../GNU/inductors.gnu ../GNU/inductors.dat
	gnuplot ../GNU/inductors.gnu
../GNU/Cesr.eps: ../GNU/Cesr.gnu ../GNU/Cesr_all.dat
	gnuplot ../GNU/Cesr.gnu
../GNU/Cesr2.eps: ../GNU/Cesr2.gnu ../GNU/Cesr2_all.dat
	gnuplot ../GNU/Cesr2.gnu
../GNU/res_esr.eps: ../GNU/rmess_esr.gnu ../GNU/rmess-esr.dat
	gnuplot ../GNU/rmess_esr.gnu
../GNU/Elco_esr.eps: ../GNU/Elco_esr.gnu ../GNU/Elco_esr.dat
	gnuplot ../GNU/Elco_esr.gnu
../GNU/frequency-ppm.eps: ../GNU/frequency-ppm.gnu ../GNU/frequency-ppm.dat
	gnuplot ../GNU/frequency-ppm.gnu
../GNU/Cap_FC_data.eps: ../GNU/Cap_FC_data.gnu ../GNU/Cap6_FC_ESR.dat ../GNU/Cap16_FC_ESR.dat ../GNU/Cap35_FC_ESR.dat ../GNU/Cap63_FC_ESR.dat
	gnuplot ../GNU/Cap_FC_data.gnu
../GNU/Cap_FR_data.eps: ../GNU/Cap_FR_data.gnu ../GNU/Cap6_FR_ESR.dat ../GNU/Cap16_FR_ESR.dat ../GNU/Cap35_FR_ESR.dat ../GNU/Cap63_FR_ESR.dat
	gnuplot ../GNU/Cap_FR_data.gnu
../GNU/Cap_FC_FR_data.eps: ../GNU/Cap_FC_FR_data.gnu ../GNU/Cap25_FC_ESR.dat ../GNU/Cap25_FR_ESR.dat
	gnuplot ../GNU/Cap_FC_FR_data.gnu

../FIG/Messung.eps: ../FIG/Messung.fig
	fig2eps $<
../FIG/port.eps: ../FIG/port.fig
	fig2eps $<
../FIG/terminal.eps: ../FIG/terminal.fig
	fig2eps $<
../FIG/ResistormessH1.eps: ../FIG/ResistormessH1.fig
	fig2eps $<
../FIG/ResistormessH2.eps: ../FIG/ResistormessH2.fig
	fig2eps $<
../FIG/ResistormessL1.eps: ../FIG/ResistormessL1.fig
	fig2eps $<
../FIG/ResistormessL2.eps: ../FIG/ResistormessL2.fig
	fig2eps $<
../FIG/Bigcap.eps: ../FIG/Bigcap.fig
	fig2eps $<
../FIG/Comparat.eps: ../FIG/Comparat.fig
	fig2eps $<
../FIG/Test2.eps: ../FIG/Test2.fig
	fig2eps $<
../FIG/Test7.eps: ../FIG/Test7.fig
	fig2eps $<
../FIG/Test8.eps: ../FIG/Test8.fig
	fig2eps $<
../FIG/PNPcc.eps: ../FIG/PNPcc.fig
	fig2eps $<
../FIG/PNPce.eps: ../FIG/PNPce.fig
	fig2eps $<
../FIG/NPNce.eps: ../FIG/NPNce.fig
	fig2eps $<
../FIG/JFETcd.eps: ../FIG/JFETcd.fig
	fig2eps $<
../FIG/ttester.eps: ../FIG/ttester.fig
	fig2eps $<
../FIG/t644tester.eps: ../FIG/t644tester.fig
	fig2eps $<
../FIG/relay_addon.eps: ../FIG/relay_addon.fig
	fig2eps $<
../FIG/diode_addon.eps: ../FIG/diode_addon.fig
	fig2eps $<
../FIG/Frequency_addon.eps: ../FIG/Frequency_addon.fig
	fig2eps $<
../FIG/zener_exp.eps: ../FIG/zener_exp.fig
	fig2eps $<
../FIG/Inductance.eps: ../FIG/Inductance.fig
	fig2eps $<
../FIG/Cap_equiv.eps: ../FIG/Cap_equiv.fig
	fig2eps $<
../FIG/Cap_esr.eps: ../FIG/Cap_esr.fig
	fig2eps $<
../FIG/Cap_esr2.eps: ../FIG/Cap_esr2.fig
	fig2eps $<
../FIG/Cap_esr2_timing.eps: ../FIG/Cap_esr2_timing.fig
	fig2eps $<
../FIG/CheckSemi1.eps: ../FIG/CheckSemi1.fig
	fig2eps $<
../FIG/CheckSemi2.eps: ../FIG/CheckSemi2.fig
	fig2eps $<
../FIG/CheckSemi3.eps: ../FIG/CheckSemi3.fig
	fig2eps $<

../FIG/BJT_AD161.eps: ../FIG/BJT_AD161.fig
	fig2eps $<
../FIG/BJT_AD162.eps: ../FIG/BJT_AD162.fig
	fig2eps $<
../FIG/BJT_BC639.eps: ../FIG/BJT_BC639.fig
	fig2eps $<
../FIG/BJT_BC640.eps: ../FIG/BJT_BC640.fig
	fig2eps $<
../FIG/BJT_BU508D.eps: ../FIG/BJT_BU508D.fig
	fig2eps $<
../FIG/BJT_BC516.eps: ../FIG/BJT_BC516.fig
	fig2eps $<
../FIG/BJT_BC517.eps: ../FIG/BJT_BC517.fig
	fig2eps $<
../FIG/BJT_BDV64.eps: ../FIG/BJT_BDV64.fig
	fig2eps $<
../FIG/BJT_BDV65.eps: ../FIG/BJT_BDV65.fig
	fig2eps $<
../FIG/JFET_BF245.eps: ../FIG/JFET_BF245.fig
	fig2eps $<
../FIG/JFET_J175.eps: ../FIG/JFET_J175.fig
	fig2eps $<
../FIG/MOS_BSS169.eps: ../FIG/MOS_BSS169.fig
	fig2eps $<
../FIG/MOS_BUZ71.eps: ../FIG/MOS_BUZ71.fig
	fig2eps $<
../FIG/MOS_IRF5305.eps: ../FIG/MOS_IRF5305.fig
	fig2eps $<
../FIG/GPS_UP501.eps: ../FIG/GPS_UP501.fig
	fig2eps $<
../FIG/GPS_GNS701.eps: ../FIG/GPS_GNS701.fig
	fig2eps $<
../FIG/rotary_encoder.eps: ../FIG/rotary_encoder.fig
	fig2eps $<
../FIG/rotary_extension.eps: ../FIG/rotary_extension.fig
	fig2eps $<
../FIG/rotary_bouncing.eps: ../FIG/rotary_bouncing.fig
	fig2eps $<
../FIG/Fish8840.eps: ../FIG/Fish8840.fig
	fig2eps $<
../FIG/ST7565lcd.eps: ../FIG/ST7565lcd.fig
	fig2eps $<
../FIG/ST7920interface.eps: ../FIG/ST7920interface.fig
	fig2eps $<
../FIG/ST7108serial164.eps: ../FIG/ST7108serial164.fig
	fig2eps $<

TEXLIST1 =  00-preface.tex 10-features.tex 20-hardware.tex 30-manual.tex 40-configuring.tex
TEXLIST1 += 50-measurement.tex 51-semicon.tex 52-resistors.tex 53-capacitors.tex 54-inductors.tex 55-selftest.tex 56-frequency.tex
TEXLIST1 += 60-generators.tex 70-errors.tex 80-special.tex 90-todo.tex

TEXLIST2 = BJT-transistors.tex MOS-transistors.tex

ttester.pdf: ttester.tex $(LISTE1) $(TEXLIST1)
	pdflatex --shell-escape ttester.tex
	pdflatex --shell-escape ttester.tex

ttinfo.pdf: ttinfo.tex $(LISTE2) $(TEXLIST2)
	pdflatex --shell-escape ttinfo.tex
	pdflatex --shell-escape ttinfo.tex
clean:
	rm $(LISTE1) $(LISTE2)
