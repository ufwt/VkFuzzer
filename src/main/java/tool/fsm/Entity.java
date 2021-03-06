package tool.fsm;

import org.statefulj.persistence.annotations.State;
import tool.Main;
import tool.configs.Config;
import tool.configs.GlobalState;
import tool.fuzzer.Component;
import tool.utils.TemplateEngine;

import java.io.StringWriter;
import java.io.Writer;
import java.util.ArrayList;

/**
 * Created by constantinos on 30/03/2016.
 * Entity base class
 */
public abstract class Entity {
    final protected Writer writer;
    final protected GlobalState globalState;
    final protected Component component;
    final protected TemplateEngine templateEngine;
    final protected ArrayList<String> visitedStates;
    @State
    protected String state;

    // Default constructor
    public Entity(final String templateFolder, final GlobalState globalState,
                  final Component component) {
        this(templateFolder, globalState, component, new ArrayList<>());
    }

    // Used for program minimization
    public Entity(final String templateFolder,
                  final GlobalState globalState,
                  final Component component,
                  final ArrayList<String> visitedStates) {
        writer = new StringWriter();
        templateEngine = new TemplateEngine(templateFolder, Main.class);
        this.visitedStates = visitedStates;
        this.globalState = globalState;
        this.component = component;
    }

    public abstract boolean generateStateCode();
    public abstract void generateStateCode(final String state, final Config config);
    public abstract void saveGeneratedProgram(final String output);
}
