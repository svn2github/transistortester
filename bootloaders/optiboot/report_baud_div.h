/* report_baud_div.h is a laborious way to report the CPP setting of BAUD_DIV */
/* I have not found a way to print the content of a defined constant freom the C proprocessor */
/* with #if 0 the output is disabled, so the 'include "report_baud_div"' can stay at its place. */

#if 0
#ifdef UART_MODE_2X
 #warning "Double speed mode UART"
#else
 #warning  "Single speed mode UART"
#endif

#define BAUD_DT (BAUD_DIV / 1000)
#define BAUD_DH (BAUD_DIV - (BAUD_DT * 1000))
#if BAUD_DT == 0
 #warning "BAUD_DIV/1000 is 0"
#elif BAUD_DT == 1
 #warning "BAUD_DIV/1000 is 1"
#elif BAUD_DT == 2
 #warning "BAUD_DIV/1000 is 2"
#elif BAUD_DT == 3
 #warning "BAUD_DIV/1000 is 3"
#elif BAUD_DT == 4
 #warning "BAUD_DIV/1000 is 4"
#else
 #warning "BAUD_DIV/1000 is >4"
#endif

#if BAUD_DH < 10
 #warning "BAUD_DIV is t00x"
#elif BAUD_DH < 20
 #warning "BAUD_DIV is t01x"
#elif BAUD_DH < 30
 #warning "BAUD_DIV is t02x"
#elif BAUD_DH < 40
 #warning "BAUD_DIV is t03x"
#elif BAUD_DH < 50
 #warning "BAUD_DIV is t04x"
#elif BAUD_DH < 60
 #warning "BAUD_DIV is t05x"
#elif BAUD_DH < 70
 #warning "BAUD_DIV is t06x"
#elif BAUD_DH < 80
 #warning "BAUD_DIV is t07x"
#elif BAUD_DH < 90
 #warning "BAUD_DIV is t08x"
#elif BAUD_DH < 100
 #warning "BAUD_DIV is t09x"
#elif BAUD_DH < 110
 #warning "BAUD_DIV is t10x"
#elif BAUD_DH < 120
 #warning "BAUD_DIV is t11x"
#elif BAUD_DH < 130
 #warning "BAUD_DIV is t12x"
#elif BAUD_DH < 140
 #warning "BAUD_DIV is t13x"
#elif BAUD_DH < 150
 #warning "BAUD_DIV is t14x"
#elif BAUD_DH < 160
 #warning "BAUD_DIV is t15x"
#elif BAUD_DH < 170
 #warning "BAUD_DIV is t16x"
#elif BAUD_DH < 180
 #warning "BAUD_DIV is t17x"
#elif BAUD_DH < 190
 #warning "BAUD_DIV is t18x"
#elif BAUD_DH < 200
 #warning "BAUD_DIV is t19x"
#elif BAUD_DH < 210
 #warning "BAUD_DIV is t20x"
#elif BAUD_DH < 220
 #warning "BAUD_DIV is t21x"
#elif BAUD_DH < 230
 #warning "BAUD_DIV is t22x"
#elif BAUD_DH < 240
 #warning "BAUD_DIV is t23x"
#elif BAUD_DH < 250
 #warning "BAUD_DIV is t24x"
#elif BAUD_DH < 260
 #warning "BAUD_DIV is t25x"
#elif BAUD_DH < 270
 #warning "BAUD_DIV is t26x"
#elif BAUD_DH < 280
 #warning "BAUD_DIV is t27x"
#elif BAUD_DH < 290
 #warning "BAUD_DIV is t28x"
#elif BAUD_DH < 300
 #warning "BAUD_DIV is t29x"
#elif BAUD_DH < 310
 #warning "BAUD_DIV is t30x"
#elif BAUD_DH < 320
 #warning "BAUD_DIV is t31x"
#elif BAUD_DH < 330
 #warning "BAUD_DIV is t32x"
#elif BAUD_DH < 340
 #warning "BAUD_DIV is t33x"
#elif BAUD_DH < 350
 #warning "BAUD_DIV is t34x"
#elif BAUD_DH < 360
 #warning "BAUD_DIV is t35x"
#elif BAUD_DH < 370
 #warning "BAUD_DIV is t36x"
#elif BAUD_DH < 380
 #warning "BAUD_DIV is t37x"
#elif BAUD_DH < 390
 #warning "BAUD_DIV is t38x"
#elif BAUD_DH < 400
 #warning "BAUD_DIV is t39x"
#elif BAUD_DH < 410
 #warning "BAUD_DIV is t40x"
#elif BAUD_DH < 420
 #warning "BAUD_DIV is t41x"
#elif BAUD_DH < 430
 #warning "BAUD_DIV is t42x"
#elif BAUD_DH < 440
 #warning "BAUD_DIV is t43x"
#elif BAUD_DH < 450
 #warning "BAUD_DIV is t44x"
#elif BAUD_DH < 460
 #warning "BAUD_DIV is t45x"
#elif BAUD_DH < 470
 #warning "BAUD_DIV is t46x"
#elif BAUD_DH < 480
 #warning "BAUD_DIV is t47x"
#elif BAUD_DH < 490
 #warning "BAUD_DIV is t48x"
#elif BAUD_DH < 500
 #warning "BAUD_DIV is t49x"
#elif BAUD_DH < 510
 #warning "BAUD_DIV is t50x"
#elif BAUD_DH < 520
 #warning "BAUD_DIV is t51x"
#elif BAUD_DH < 530
 #warning "BAUD_DIV is t52x"
#elif BAUD_DH < 540
 #warning "BAUD_DIV is t53x"
#elif BAUD_DH < 550
 #warning "BAUD_DIV is t54x"
#elif BAUD_DH < 560
 #warning "BAUD_DIV is t55x"
#elif BAUD_DH < 570
 #warning "BAUD_DIV is t56x"
#elif BAUD_DH < 580
 #warning "BAUD_DIV is t57x"
#elif BAUD_DH < 590
 #warning "BAUD_DIV is t58x"
#elif BAUD_DH < 600
 #warning "BAUD_DIV is t59x"
#elif BAUD_DH < 610
 #warning "BAUD_DIV is t60x"
#elif BAUD_DH < 620
 #warning "BAUD_DIV is t61x"
#elif BAUD_DH < 630
 #warning "BAUD_DIV is t62x"
#elif BAUD_DH < 640
 #warning "BAUD_DIV is t63x"
#elif BAUD_DH < 650
 #warning "BAUD_DIV is t64x"
#elif BAUD_DH < 660
 #warning "BAUD_DIV is t65x"
#elif BAUD_DH < 670
 #warning "BAUD_DIV is t66x"
#elif BAUD_DH < 680
 #warning "BAUD_DIV is t67x"
#elif BAUD_DH < 690
 #warning "BAUD_DIV is t68x"
#elif BAUD_DH < 700
 #warning "BAUD_DIV is t69x"
#elif BAUD_DH < 710
 #warning "BAUD_DIV is t70x"
#elif BAUD_DH < 720
 #warning "BAUD_DIV is t71x"
#elif BAUD_DH < 730
 #warning "BAUD_DIV is t72x"
#elif BAUD_DH < 740
 #warning "BAUD_DIV is t73x"
#elif BAUD_DH < 750
 #warning "BAUD_DIV is t74x"
#elif BAUD_DH < 760
 #warning "BAUD_DIV is t75x"
#elif BAUD_DH < 770
 #warning "BAUD_DIV is t76x"
#elif BAUD_DH < 780
 #warning "BAUD_DIV is t77x"
#elif BAUD_DH < 790
 #warning "BAUD_DIV is t78x"
#elif BAUD_DH < 800
 #warning "BAUD_DIV is t79x"
#elif BAUD_DH < 810
 #warning "BAUD_DIV is t80x"
#elif BAUD_DH < 820
 #warning "BAUD_DIV is t81x"
#elif BAUD_DH < 830
 #warning "BAUD_DIV is t82x"
#elif BAUD_DH < 840
 #warning "BAUD_DIV is t83x"
#elif BAUD_DH < 850
 #warning "BAUD_DIV is t84x"
#elif BAUD_DH < 860
 #warning "BAUD_DIV is t85x"
#elif BAUD_DH < 870
 #warning "BAUD_DIV is t86x"
#elif BAUD_DH < 880
 #warning "BAUD_DIV is t87x"
#elif BAUD_DH < 890
 #warning "BAUD_DIV is t88x"
#elif BAUD_DH < 900
 #warning "BAUD_DIV is t89x"
#elif BAUD_DH < 910
 #warning "BAUD_DIV is t90x"
#elif BAUD_DH < 920
 #warning "BAUD_DIV is t91x"
#elif BAUD_DH < 930
 #warning "BAUD_DIV is t92x"
#elif BAUD_DH < 940
 #warning "BAUD_DIV is t93x"
#elif BAUD_DH < 950
 #warning "BAUD_DIV is t94x"
#elif BAUD_DH < 960
 #warning "BAUD_DIV is t95x"
#elif BAUD_DH < 970
 #warning "BAUD_DIV is t96x"
#elif BAUD_DH < 980
 #warning "BAUD_DIV is t97x"
#elif BAUD_DH < 990
 #warning "BAUD_DIV is t98x"
#elif BAUD_DH < 1000
 #warning "BAUD_DIV is t99x"
#endif
#if (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 0
 #warning "BAUD_DIV x=0"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 1
 #warning "BAUD_DIV x=1"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 2
 #warning "BAUD_DIV x=2"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 3
 #warning "BAUD_DIV x=3"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 4
 #warning "BAUD_DIV x=4"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 5
 #warning "BAUD_DIV x=5"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 6
 #warning "BAUD_DIV x=6"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 7
 #warning "BAUD_DIV x=7"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 8
 #warning "BAUD_DIV x=8"
#elif (BAUD_DIV - ((BAUD_DIV / 10) * 10)) == 9
 #warning "BAUD_DIV x=9"
#else
 #warning "BAUD_DIV x=?"
#endif
/* remove interim #define's */
#undef BAUD_DT
#undef BAUD_DH 
#endif  /* 0 or 1 if */
