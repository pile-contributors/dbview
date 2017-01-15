DbView
=======

DbView pile provides a table-like widget enhanced to correctly show paginated results loaded asynchronous. Its best use is to present data from a database with a high number of rows and over a possibly slow connection.

Main class for the pile is DbView representing a table-like widget. It is actually a complex widget containing a tableview,  buttons for pages  navigation, buttons for number of rows per page and download ability.

First layer of data negotiation is performed by an internal model - InMo - that the user cannot access directly. The InMo 
inherits from abstract table model in qt and is selected inside the tableview. Actions requested by the user are mostly forwarded to this model and visual aspects of the widgets are updated in response to it changing.

The user provides the data in the form of a class that inherits from DbViewMo class. If this in a model that has all its data in memory then there is already a class derived from DbViewMo that can do that for you: DbViewMoSi. If, on the other hand, the data is on a database, for example, then you should implement a DbViewMo-derived class that translates the requests from the model into database requests then, when the result arrives, caches it.

Sorting
------------

The tableview sorting is used when no filter is installed. If there is ...

Filtering
--------------

A special widget derived from standard header is used to allow inserting widgets in column headers. The user may choose to filter by string pattern or with list among others but it boils down to an DbView filter that is created behind the scenes. The filter must be capable of creating a widget for the column.

