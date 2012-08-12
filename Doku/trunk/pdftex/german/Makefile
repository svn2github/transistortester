LISTE = ../GNU/RLvtot.eps ../GNU/RLvlow.eps ../GNU/RLvhigh.eps ../GNU/RHv.eps ../GNU/rmess.eps
LISTE += ../GNU/Mega8cap.eps ../GNU/Mega168cap.eps ../GNU/Mega168cap_opt.eps ../GNU/Mega168all.eps 
LISTE += ../GNU/ComparatorAdjust.eps
LISTE += ../FIG/Messung.eps ../FIG/port.eps ../FIG/ResistormessH1.eps ../FIG/ResistormessH2.eps ../FIG/ResistormessL1.eps
LISTE += ../FIG/ResistormessL2.eps ../FIG/ResistormessRH1.eps ../FIG/terminal.eps
LISTE += ../FIG/Comparat.eps ../FIG/Test2.eps ../FIG/Test7.eps ../FIG/Test8.eps ../FIG/Bigcap.eps
LISTE += ../FIG/PNPcc.eps ../FIG/PNPce.eps ../FIG/NPNce.eps ../FIG/ttester.eps
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
../GNU/ComparatorAdjust.eps: ../GNU/comparator_diff.gnu ../GNU/comparator_cap.dat
	gnuplot ../GNU/comparator_diff.gnu
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
../FIG/ttester.eps: ../FIG/ttester.fig
	fig2eps ../FIG/ttester.fig
TEXLIST =  capacitors.tex configuring.tex errors.tex features.tex hardware.tex measurement.tex preface.tex resistors.tex selftest.tex semicon.tex special.tex todo.tex
ttester.pdf: ttester.tex $(LISTE) $(TEXLIST)
	pdflatex --shell-escape ttester.tex
	touch ttester.tex
clean:
	rm ../GNU/RLv*.eps ../GNU/RLv*.pdf ../GNU/RHv.eps ../GNU/RHv.pdf
