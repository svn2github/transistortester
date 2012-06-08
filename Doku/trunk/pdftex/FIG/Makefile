#
# fig4latex makefile
#

all: ResistormessL2.tex ResistormessL1.tex ResistormessH2.tex Messung.tex ResistormessH1.tex terminal.tex port.tex

# translation into pstex

ResistormessL2.tex: ResistormessL2.eps 
	fig2dev -L pstex_t -p ./ResistormessL2.eps -m 1 ResistormessL2.fig > ResistormessL2.tex

ResistormessL2.pdf: ResistormessL2.eps 
	epstopdf ResistormessL2.eps

ResistormessL2.eps: ResistormessL2.fig 
	fig2dev -L pstex -m 1 ResistormessL2.fig > ResistormessL2.eps

clean::
	rm -f ResistormessL2.tex ResistormessL2.eps ResistormessL2.pdf


# translation into pstex

ResistormessL1.tex: ResistormessL1.eps 
	fig2dev -L pstex_t -p ./ResistormessL1.eps -m 1 ResistormessL1.fig > ResistormessL1.tex

ResistormessL1.pdf: ResistormessL1.eps 
	epstopdf ResistormessL1.eps

ResistormessL1.eps: ResistormessL1.fig 
	fig2dev -L pstex -m 1 ResistormessL1.fig > ResistormessL1.eps

clean::
	rm -f ResistormessL1.tex ResistormessL1.eps ResistormessL1.pdf


# translation into pstex

ResistormessH2.tex: ResistormessH2.eps 
	fig2dev -L pstex_t -p ./ResistormessH2.eps -m 1 ResistormessH2.fig > ResistormessH2.tex

ResistormessH2.pdf: ResistormessH2.eps 
	epstopdf ResistormessH2.eps

ResistormessH2.eps: ResistormessH2.fig 
	fig2dev -L pstex -m 1 ResistormessH2.fig > ResistormessH2.eps

clean::
	rm -f ResistormessH2.tex ResistormessH2.eps ResistormessH2.pdf


# translation into pstex

Messung.tex: Messung.eps 
	fig2dev -L pstex_t -p ./Messung.eps -m 1 Messung.fig > Messung.tex

Messung.pdf: Messung.eps 
	epstopdf Messung.eps

Messung.eps: Messung.fig 
	fig2dev -L pstex -m 1 Messung.fig > Messung.eps

clean::
	rm -f Messung.tex Messung.eps Messung.pdf


# translation into pstex

ResistormessH1.tex: ResistormessH1.eps 
	fig2dev -L pstex_t -p ./ResistormessH1.eps -m 1 ResistormessH1.fig > ResistormessH1.tex

ResistormessH1.pdf: ResistormessH1.eps 
	epstopdf ResistormessH1.eps

ResistormessH1.eps: ResistormessH1.fig 
	fig2dev -L pstex -m 1 ResistormessH1.fig > ResistormessH1.eps

clean::
	rm -f ResistormessH1.tex ResistormessH1.eps ResistormessH1.pdf


# translation into pstex

terminal.tex: terminal.eps 
	fig2dev -L pstex_t -p ./terminal.eps -m 1 terminal.fig > terminal.tex

terminal.pdf: terminal.eps 
	epstopdf terminal.eps

terminal.eps: terminal.fig 
	fig2dev -L pstex -m 1 terminal.fig > terminal.eps

clean::
	rm -f terminal.tex terminal.eps terminal.pdf


# translation into pstex

port.tex: port.eps 
	fig2dev -L pstex_t -p ./port.eps -m 1 port.fig > port.tex

port.pdf: port.eps 
	epstopdf port.eps

port.eps: port.fig 
	fig2dev -L pstex -m 1 port.fig > port.eps

clean::
	rm -f port.tex port.eps port.pdf


