<map version="freeplane 1.5.9">
<!--To view this file, download free mind mapping software Freeplane from http://freeplane.sourceforge.net -->
<node TEXT="No-OS-Design" FOLDED="false" ID="ID_1618157895" CREATED="1495783471574" MODIFIED="1495783501380" STYLE="oval">
<font SIZE="18"/>
<hook NAME="MapStyle">
    <properties fit_to_viewport="false;"/>

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node" STYLE="oval" UNIFORM_SHAPE="true" VGAP_QUANTITY="24.0 pt">
<font SIZE="24"/>
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="default" COLOR="#000000" STYLE="fork">
<font NAME="SansSerif" SIZE="10" BOLD="false" ITALIC="false"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.attributes">
<font SIZE="9"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.note" COLOR="#000000" BACKGROUND_COLOR="#ffffff" TEXT_ALIGN="LEFT"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important">
<icon BUILTIN="yes"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right" STYLE="bubble">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000" STYLE="oval" SHAPE_HORIZONTAL_MARGIN="10.0 pt" SHAPE_VERTICAL_MARGIN="10.0 pt">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#0033ff">
<font SIZE="16"/>
<edge COLOR="#ff0000"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#00b439">
<font SIZE="14"/>
<edge COLOR="#0000ff"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#990000">
<font SIZE="12"/>
<edge COLOR="#00ff00"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#111111">
<font SIZE="10"/>
<edge COLOR="#ff00ff"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,5">
<edge COLOR="#00ffff"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,6">
<edge COLOR="#7c0000"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,7">
<edge COLOR="#00007c"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,8">
<edge COLOR="#007c00"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,9">
<edge COLOR="#7c007c"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,10">
<edge COLOR="#007c7c"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,11">
<edge COLOR="#7c7c00"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="6" RULE="ON_BRANCH_CREATION"/>
<node TEXT="We gain more stack and queue memory without OS in resource limited environment." POSITION="right" ID="ID_1666099287" CREATED="1495783544385" MODIFIED="1495783598152">
<edge COLOR="#ff0000"/>
</node>
<node TEXT="Beyond thread mode, we have only 510Bytes stack at max, that require us to design code snippets carefully, we can&apos;t use large or too more local variables and arguments. Even we can do it, third-party libraries won&apos;t see it that way, may third-party libraries only works for simple Arduino environment, they not been test in resources limited environment." POSITION="right" ID="ID_748279695" CREATED="1495783637802" MODIFIED="1495784009761">
<edge COLOR="#0000ff"/>
</node>
<node TEXT="So, we restrict programmer to use coroutine design and only have one main thread with all resources we have!" POSITION="right" ID="ID_1982739604" CREATED="1495784015544" MODIFIED="1495784086477">
<edge COLOR="#ff00ff"/>
</node>
<node TEXT="How to do realtime stuff?" POSITION="right" ID="ID_907649081" CREATED="1495784091105" MODIFIED="1495784399673">
<edge COLOR="#00ffff"/>
<node TEXT="Start a interrupt function with watchdog timer, do things inside the timer." ID="ID_941251249" CREATED="1495784400882" MODIFIED="1495784573184"/>
<node TEXT="Added three priority coroutine level" ID="ID_1239981459" CREATED="1495784573531" MODIFIED="1495784737589">
<node TEXT="high-priority coroutines" ID="ID_1619352839" CREATED="1495784622855" MODIFIED="1495784762205">
<node TEXT="timer calls" ID="ID_829895519" CREATED="1495784860779" MODIFIED="1495784865822"/>
</node>
<node TEXT="normal-priority coroutines" ID="ID_1596289421" CREATED="1495784699836" MODIFIED="1495784759037"/>
<node TEXT="idle-priority coroutines" ID="ID_1221475282" CREATED="1495784718484" MODIFIED="1495784753669"/>
</node>
<node TEXT="All timers operation will done immediately (There does not have a timer thread to handle the timer stuffs!)" ID="ID_104362407" CREATED="1495784976738" MODIFIED="1495785012223"/>
</node>
<node TEXT="Interrupt function will only disable itself by detachInterrupt when interrupt triggered" POSITION="right" ID="ID_657056624" CREATED="1495786671615" MODIFIED="1495786796692">
<edge COLOR="#7c0000"/>
<node TEXT="When enter interruption" ID="ID_1243849145" CREATED="1495786830581" MODIFIED="1495786844916">
<node TEXT="noInterrupts()" ID="ID_1890664629" CREATED="1495786797944" MODIFIED="1495786810785"/>
<node TEXT="detachInterrupt()" ID="ID_1747326819" CREATED="1495786815693" MODIFIED="1495786824537"/>
<node TEXT="interrupts()" ID="ID_457856477" CREATED="1495786811161" MODIFIED="1495786814880"/>
</node>
<node TEXT="Before exit interruption" ID="ID_322189706" CREATED="1495786826385" MODIFIED="1495786861038">
<node TEXT="noInterrupts()" ID="ID_1683928344" CREATED="1495786797944" MODIFIED="1495786810785"/>
<node TEXT="attachInterrupt()" ID="ID_1125307746" CREATED="1495786815693" MODIFIED="1495786871759"/>
<node TEXT="interrupts()" ID="ID_1340808739" CREATED="1495786811161" MODIFIED="1495786814880"/>
</node>
</node>
</node>
</map>
