LISTE = ../GNU/RLvtot.eps ../GNU/RLvlow.eps ../GNU/RLvhigh.eps ../GNU/RHv.eps ../GNU/rmess.eps
LISTE += ../GNU/Mega8cap.eps ../GNU/Mega168cap.eps ../GNU/Mega168cap_opt.eps ../GNU/Mega168all.eps 
LISTE += ../GNU/ComparatorAdjust.eps ../GNU/Mega328all.eps ../GNU/SelfTref.eps ../GNU/MegaAuto.eps
LISTE += ../GNU/m168res_all.eps ../GNU/induct328p.eps ../GNU/Cesr.eps ../GNU/Cesr2.eps ../GNU/res_esr.eps
LISTE += ../GNU/Elco_esr.eps
LISTE += ../FIG/Messung.eps ../FIG/port.eps ../FIG/ResistormessH1.eps ../FIG/ResistormessH2.eps ../FIG/ResistormessL1.eps
LISTE += ../FIG/ResistormessL2.eps ../FIG/ResistormessRH1.eps ../FIG/terminal.eps
LISTE += ../FIG/Comparat.eps ../FIG/Test2.eps ../FIG/Test7.eps ../FIG/Test8.eps ../FIG/Bigcap.eps
LISTE += ../FIG/PNPcc.eps ../FIG/PNPce.eps ../FIG/NPNce.eps ../FIG/ttester.eps ../FIG/relay_addon.eps ../FIG/zener_exp.eps 
LISTE += ../FIG/Inductance.eps ../FIG/JFETcd.eps ../FIG/Cap_equiv.eps ../FIG/Cap_esr.eps ../FIG/Cap_esr2.eps ../FIG/Cap_esr2_timing.eps
LISTE += ../FIG/CheckSemi1.eps ../FIG/CheckSemi2.eps
all: $(LISTE) ttester.pdf
	
../GNU/RLvtot.eps: ../GNU/RLvtot.gnu
	gnuplot ../GNU/RLvtot.gnu
../GNU/RLvlow.eps: ../GNU/RLvlow.gnu
	gnuplot ../GNU/RLvlow.gnu
../GNU/RLvhigh.eps: ../GNU/RLvhigh.gnu
	gnuplot ../GNU/RLvhigh.gnu
../GNU/RHv.eps: ../GNU/RHv.gnu
	gnuplot ../GNU/RHv.gnu
../GNU/rmess.eps: ../GNU/rmess.gnu ../GNU/rmess.dat
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
../FIG/Messung.eps: ../FIG/Messung.fig
	fig2eps ../FIG/Messung.fig
../FIG/port.eps: ../FIG/port.fig
	fig2eps ../FIG/port.fig
../FIG/terminal.eps: ../FIG/terminal.fig
	fig2eps ../FIG/terminal.fig
../FIG/ResistormessH1.eps: ../FIG/ResistormessH1.fig
	fig2eps ../FIG/ResistormessH1.fig
../FIG/ResistormessH2.eps: ../FIG/ResistormessH2.fig
	fig2eps ../FIG/ResistormessH2.fig
../FIG/ResistormessL1.eps: ../FIG/ResistormessL1.fig
	fig2eps ../FIG/ResistormessL1.fig
../FIG/ResistormessL2.eps: ../FIG/ResistormessL2.fig
	fig2eps ../FIG/ResistormessL2.fig
../FIG/Bigcap.eps: ../FIG/Bigcap.fig
	fig2eps ../FIG/Bigcap.fig
../FIG/Comparat.eps: ../FIG/Comparat.fig
	fig2eps ../FIG/Comparat.fig
../FIG/Test2.eps: ../FIG/Test2.fig
	fig2eps ../FIG/Test2.fig
../FIG/Test7.eps: ../FIG/Test7.fig
	fig2eps ../FIG/Test7.fig
../FIG/Test8.eps: ../FIG/Test8.fig
	fig2eps ../FIG/Test8.fig
../FIG/PNPcc.eps: ../FIG/PNPcc.fig
	fig2eps ../FIG/PNPcc.fig
../FIG/PNPce.eps: ../FIG/PNPce.fig
	fig2eps ../FIG/PNPce.fig
../FIG/NPNce.eps: ../FIG/NPNce.fig
	fig2eps ../FIG/NPNce.fig
../FIG/JFETcd.eps: ../FIG/JFETcd.fig
	fig2eps ../FIG/JFETcd.fig
../FIG/ttester.eps: ../FIG/ttester.fig
	fig2eps ../FIG/ttester.fig
../FIG/relay_addon.eps: ../FIG/relay_addon.fig
	fig2eps ../FIG/relay_addon.fig
../FIG/zener_exp.eps: ../FIG/zener_exp.fig
	fig2eps ../FIG/zener_exp.fig
../FIG/Inductance.eps: ../FIG/Inductance.fig
	fig2eps ../FIG/Inductance.fig
../FIG/Cap_equiv.eps: ../FIG/Cap_equiv.fig
	fig2eps ../FIG/Cap_equiv.fig
../FIG/Cap_esr.eps: ../FIG/Cap_esr.fig
	fig2eps ../FIG/Cap_esr.fig
../FIG/Cap_esr2.eps: ../FIG/Cap_esr2.fig
	fig2eps ../FIG/Cap_esr2.fig
../FIG/Cap_esr2_timing.eps: ../FIG/Cap_esr2_timing.fig
	fig2eps ../FIG/Cap_esr2_timing.fig
../FIG/CheckSemi1.eps: ../FIG/CheckSemi1.fig
	fig2eps ../FIG/CheckSemi1.fig
../FIG/CheckSemi2.eps: ../FIG/CheckSemi2.fig
	fig2eps ../FIG/CheckSemi2.fig


TEXLIST =  00-preface.tex 10-features.tex 20-hardware.tex 30-manual.tex 40-configuring.tex 50-measurement.tex 51-semicon.tex 52-resistors.tex 53-capacitors.tex \
  54-inductors.tex 55-selftest.tex 60-errors.tex 70-special.tex 80-todo.tex
ttester.pdf: ttester.tex $(LISTE) $(TEXLIST)
	pdflatex --shell-escape ttester.tex
	touch ttester.tex
clean:
	rm ../GNU/RLv*.eps ../GNU/RLv*.pdf ../GNU/RHv.eps ../GNU/RHv.pdf
