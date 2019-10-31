--- 

layout: default
title: hw2

---

# <img src="img/logo.png" width="30px"> CSCI339001 Visualization


## HW 2 - Exploratory and Explanatory Analysis with Tableau 

### Prerequisite
* Watch the first tutorial video on the [Tableau Public resource website](https://public.tableau.com/en-us/s/resources)

* Download the [Tableau Public](https://public.tableau.com/en-us/s/download)

* Be familiar with basic visualizations in ["From Data to Viz"](https://www.data-to-viz.com/)

* Read [6. Exploring Data with Simple Charts, The Truthful Art, Alberto Cairo, 2016](https://learning.oreilly.com/library/view/the-truthful-art/9780133440492/ch06.html#ch06)

* Read [Chapter 8. Pulling it all together, Storytelling with Data, Cole Nussbaumer Knaflic, 2015](https://learning.oreilly.com/library/view/storytelling-with-data/9781119002253/c08.xhtml)

* Accept the Github Classroom assignment invitation: [https://classroom.github.com/a/KHzhvWcf](https://classroom.github.com/a/KHzhvWcf)

### Instruction
In this assignment, you will explore a [dataset of interest](#part-1-data-selection) and communicate meaningful insights you found from the dataset. You will use Tableau Public for both [exploration](#part-2-exploration ) and [explanation](#part-3-explanation) activities. The outcome from the activities should be a form of a [dashboard](https://help.tableau.com/current/pro/desktop/en-us/dashboards_create.htm), [Story Points](https://help.tableau.com/current/pro/desktop/en-gb/stories.htm), [annotated chart](https://help.tableau.com/current/pro/desktop/en-us/annotations_annotations_add.htm). For submission, you should create a simple web page that [embeds](https://help.tableau.com/current/pro/desktop/en-us/shareworkbooks.htm#shareworkbooks.html) the Tableau outcome, along with a brief report on your reflection on processes, findings, and lessons learned.

### Part 1 Data Selection
First, you will need to find a **public** dataset in a topic of interest. This step can take time more than you expected. So, please start a search for the dataset as early as possible. To help you find one, here we provide a list of potential sources:

* [Tableau Public Sample Data](https://public.tableau.com/en-us/s/resources?qt-overview_resources=1#qt-overview_resources)
* [FiveThirtyEight](https://data.fivethirtyeight.com/)
* [data.world](https://data.world/datasets/open-data)
* [Data Is Plural Archive](https://tinyletter.com/data-is-plural/archive)
* [Kaggle Datasets](https://www.kaggle.com/datasets)
* [Google Dataset Search](https://toolbox.google.com/datasetsearch)
* [UN Data](http://data.un.org/)
* [World Bank Open Data](https://data.worldbank.org/)
* [World Health Organization](https://www.who.int/gho/en/)
* [OECD](https://data.oecd.org/)
* [UNICEF](https://data.unicef.org/)
* [IMF (International Monetary Fund)](https://www.imf.org/en/Data)
* [NOAA (National Center for Environmental Information)](https://www.ncdc.noaa.gov/cdo-web/datasets)
* [U.S. Government Open Data](https://www.data.gov/)

We recommend that you find a relatively clean dataset which does not require tedious preprocessing. For simple data processing such as filtering, deriving new columns, or joining multiple tables, you can use Tableau or your familiar spreadsheet tools like Excel.

### Part 2 Exploration
*What do you want to know about?*

#### Step 1. Ask Questions
> "Far better an approximate answer to the right question, which is often vague, than an exact answer to the wrong question, which can always be made precise." — John Tukey

You need to come up with questions to guide your investigation toward a better understanding of your data. **Prior to analysis, formulate your initial hypotheses as questions** as many and as diverse as possible. This will help you avoid potential confirmation (or other types of) bias during your analysis by gaining multiple perspectives about the data.

#### Step 2. Generate Visualizations

Now, you generate visualizations to answer your initial set of questions. You may start by visualizing **distributions** (count, temporal, geographical) of single data variables and **relationships** between multiple variables. You may also inspect potential issues with data quality (e.g., missing data or strong outliers).

 A new set of questions might arise while confirming/disproving your initial hypotheses through the visual data analysis. Remember exploratory data analysis is an **iterative process**, requiring multiple phases of question and answering.

 Whenever you find something interesting, you should **record it as a worksheet in Tableau, along with an annotative note** describing your takeaway. You need to **iterate** Step 2 and Step 3 multiple times to find useful insights.

### Part 3 Explanation

*What do you want to share with others?*

#### Step 1. Turn Insights into Story Bits
At this point, you will have a series of Tableau worksheets summarizing insights you found during the exploration phase. Now it's time to turn those insights into story bits. 

The visualizations in the worksheets themselves are often not ready for communication. You should employ **annotations and highlights** as necessary to provide guidance to your audience by clearly indicating what is important and meaningful. Also, don't forget to add a **good** title, axes labels, and legends as needed.

Tableau will mostly provide a good enough visual design but you should also consider **avoiding visual clutter** or choosing a **better visual** to draw an attention from the audience without sacrificing the readability of the underlying message.

#### Step 2. Narrative Design

When making a data-driven story, you should first think about what message you want to communicate. You are then interested in conveying the message most effectively through a compelling narrative structure. 

You put the multiple story bits together into a story. How do you want to **arrange** them so that your audience can easily follow through? Is a visualization too complex for the audience to understand? Do you need to **break it into multiple pieces** to build up the visualization? Do you want to tell your story in a **chronological** order or make it **nonlinear**?


Also, you want to think about what format of your data story will be, whether it will take a form of an **annotated chart** (or infographics), a **dashboard**, or **Story Points**. Do you want to make it **author-driven** (explanatory), **reader-driven** (explanatory), or mixed?

Data storytelling is also a **creative process**, requiring experimentations with different narrative designs. You may also want to **go back to the exploration stage** as necessary to gain additional supporting evidence or investigate different story directions.

Once you are done, you need to [**publish your Tableau workbook online**](https://help.tableau.com/current/pro/desktop/en-gb/publish_workbooks_tableaupublic.htm). Tableau Public does not actually allow you to save your workbook locally. Thus, you should not use any private data.

### Part 4. Presentation & Submission

#### Final Deliverable

You need to create a simple web page (no Javascript needed) to showcase your work. Overall, your web page should have two parts: 1) [embedded Tableau workbook](https://help.tableau.com/current/pro/desktop/en-us/shareworkbooks.htm#shareworkbooks.html) (an annotated chart, dashboard or Story Points) and 2) your **reflection on processes, findings, and lessons** learned. Also, don't forget to **mention the data source** in your workbook or web page.

In the reflection part, you essentially describe **the backstory of your project**. Imagine you are writing an article about your analysis. You can describe what you did in each stage, things that are not included in the workbook, alternative narrative designs you experimented. You should include **at least a paragraph and an image for each stage** (data selection, exploration, explanation stages). For example, why did you find the topic interesting, what were the questions you had, what hurdles did you run into? why did you decide not to include certain visualizations? what was your initial story structure? etc.


#### Submission

You need to submit your final web page through Github Classroom. Please find the assignment invitation here: [https://classroom.github.com/a/KHzhvWcf](https://classroom.github.com/a/KHzhvWcf).

You need to push your web page to the remote repository you accepted through the assignment invitation and test it online. Again, you need to go to the Settings page to enable "Github Pages"; use the master branch as the source for Github Pages. If everything goes smoothly, your homework will be available on this url: ```https://bcviscourse.github.io/hw2-[username]/``` Finally, please submit the working url on Canvas. We will use the url to grade your homework. 

*Thank you!*
