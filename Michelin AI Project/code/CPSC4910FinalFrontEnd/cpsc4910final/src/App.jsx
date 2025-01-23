import React, { useState, useEffect, useRef } from "react";
import { BrowserRouter as Router, Route, Routes, Link } from "react-router-dom";
import CommonQueries from "./CommonQueries";
import "./App.css";

function App() {
    /* Setting up state variables */
    const [query, setQuery] = useState("");
    const [QG, setQG] = useState({});
    const [activeQG, setActiveQG] = useState(null);
    const [showOverlay, setShowOverlay] = useState(false);
    const [newQGName, setNewQGName] = useState("");
    const [renameQG, setRenameQG] = useState(null);
    const [queryList, setQueryList] = useState({});
    const bubblesRef = useRef(null);

    /* Creates a new query group with a list of empty messages
    and makes it the active query group. Resets the overlay.*/
    const addNewQG = () => {
        const newQG = {
            name: newQGName,
            lastActive: Date.now(),
            messages: [],
        };
        setQG((prevQG) => ({ ...prevQG, [newQGName]: newQG, }));
        setActiveQG(newQGName);
        setNewQGName("");
        setShowOverlay(false);
    };

    /* Handles if a query from the Common Queries is clicked */
    const commonQueryClick = (queryText, navigate) => {
        let response;

        /* Ifthe query clicked is one of the hard-coded inputs, then it outputs
        the hard coded output.*/
        if (queryText === "What does checkDuplicate do?") {
            response = "The `checkDuplicate` function takes a linked list (`head`) and a potential addition (`add`) as input, and returns `true` if the `add` node is already present in the list, indicating a duplicate, or `false` otherwise. It iterates over the list, comparing members of the `add` node with those of each node in the list until it finds a match or reaches the end of the list.";
        } else if (queryText === "How many columns wide is the printed border?") {
            response = "The printed border is 80 columns wide. The function `printBorder` uses a loop from 0 to 79 to print asterisks (*), resulting in an 80-column-wide border.";
        } else if (queryText === "Does this code allow duplicate list entries?") {
            response = "The code allows checking for duplicate list entries when adding a new node to the list via the `add` function, which calls the `checkDuplicate` function. However, it does not explicitly disallow duplicates during sorting or other operations. Therefore, whether duplicates are allowed depends on the implementation of the `checkDuplicate` function.";
        } else if (queryText === "Does this program check for leap years?") {
            response = "Yes, this program checks for leap years using the function `isLeapYear()`, which determines whether a given year is a leap year based on its divisibility rules. The function returns True if the year is a leap year and False otherwise. This result is used in another part of the code to determine the number of days in February.";
        } else {
            response = `Auto-generated response`;
        }

        /* Set's the name of the Query Group to the query clicked on */
        const QGName = `"${queryText}"`;
        const newQG = {
            name: QGName,
            lastActive: Date.now(),
            messages: [{ query: queryText, isUser: true }],
        };

        /* Adds new query to query group */
        setQG((prevQG) => ({...prevQG, [QGName]: newQG, }));

        setActiveQG(QGName);

        /* Updates list of the common queries */
        setQueryList((prevList) => {
            return { ...prevList, [queryText]: (prevList[queryText] || 0) + 1, };
        });

        navigate("/");

        /* Timeout adds delay. State is updated to have response message as part of 
        the query group. */
        setTimeout(() => {
            setQG((prevQG) => {
                const updatedQG = {...prevQG[QGName],
                    messages: [...prevQG[QGName].messages,
                        { query: response, isUser: false }, ], };
                return { ...prevQG, [QGName]: updatedQG };
            });
        }, 500);
    };

    /* If "enter" hit (after inputting new query) */
    const newInputEntered = (e) => {
        if (e.key === "Enter") {
            e.preventDefault();

            /* Makes sure query isn't blank and there is an active query group */
            if (query.trim() === "" || !activeQG) return;

            const userQuery = query;
            setQuery("");

            /* Updated query group state. Adding the new message to it */
            setQG((prevQG) => {
                const updatedQG = {...prevQG[activeQG],
                    messages: [ ...prevQG[activeQG].messages, { query: userQuery, isUser: true }, ],
                };
                return { ...prevQG, [activeQG]: updatedQG };
            });

            /* Delays output */
            setTimeout(() => {
                let response;

                /* If input is one of the ones hardcoded, puts out the hardcoded output */
                if (userQuery === "What does checkDuplicate do?") {
                    response =
                        "The `checkDuplicate` function takes a linked list (`head`) and a potential addition (`add`) as input, and returns `true` if the `add` node is already present in the list, indicating a duplicate, or `false` otherwise. It iterates over the list, comparing members of the `add` node with those of each node in the list until it finds a match or reaches the end of the list.";
                } else if (userQuery === "How many columns wide is the printed border?") {
                    response =
                        "The printed border is 80 columns wide. The function `printBorder` uses a loop from 0 to 79 to print asterisks (*), resulting in an 80-column-wide border.";
                } else if (userQuery === "Does this code allow duplicate list entries?") {
                    response = "The code allows checking for duplicate list entries when adding a new node to the list via the add function, which calls the checkDuplicate function. However, it does not explicitly disallow duplicates during sorting or other operations. Therefore, whether duplicates are allowed depends on the implementation of the checkDuplicate function.";
                } else if (userQuery === "Does this program check for leap years?") {
                    response = "Yes, this program checks for leap years using the function isLeapYear(), which determines whether a given year is a leap year based on its divisibility rules. The function returns True if the year is a leap year and False otherwise. This result is used in another part of the code to determine the number of days in February.";
                } else {
                    response = `Auto-generated response`;
                }

                /* Updated query group state. Adding the new message to it */
                setQG((prevQG) => {
                    const updatedQG = { ...prevQG[activeQG],
                        messages: [ ...prevQG[activeQG].messages, { query: response, isUser: false }, ],
                    };
                    return { ...prevQG, [activeQG]: updatedQG };
                });

                /* Updates list of the common queries */
                setQueryList((prevList) => {
                    return { ...prevList, [userQuery]: (prevList[userQuery] || 0) + 1, };
                });
            }, 500);
        }
    };



    /* Clears all of the messages within the active query group */
    const clearBubbles = () => {
        if (activeQG) {
            setQG((prevQG) => {
                const clearedQG = { ...prevQG };
                clearedQG[activeQG].messages = [];
                return clearedQG;
            });
        }
    };

    /* Automatically scrolls to bottom of messages within query group */
    useEffect(() => {
        if (bubblesRef.current) { bubblesRef.current.scrollTop = bubblesRef.current.scrollHeight; }
    }, [QG, activeQG]);

    /* Sorts query groups by last active */
    const sortedQG = Object.keys(QG).sort((a, b) => QG[b].lastActive - QG[a].lastActive);


    
    return (
        <Router>
            <div className="App"> 
                <div className="sidebar"> 
                    <h2 className="query-groups-title">Query Groups</h2> 
                    <button onClick={() => setShowOverlay(true)}>+ New Query Group</button> 
                    <ul>
                        {/* creates a list for each query group */}
                        {sortedQG.map((QGName) => (
                            <li 
                                key={QGName}
                                onClick={() => {
                                    setActiveQG(QGName);
                                    setQG((prevQG) => ({...prevQG, [QGName]: {...prevQG[QGName], lastActive: Date.now(), }, }));
                                }}
                                className={activeQG === QGName ? "active" : ""} >
                                {QGName}
                            </li>
                        ))}
                    </ul>
                    { /* Establishes buttons */ }
                    <div className="sidebarButtons">
                        <button
                            className="clearButton"
                            onClick={clearBubbles}
                            disabled={!activeQG} >
                            Clear
                        </button>
                        <button
                            className="deleteButton"
                            onClick={() =>
                                setQG((prevQG) => {
                                    const updatedQG = { ...prevQG };
                                    delete updatedQG[activeQG];
                                    return updatedQG;
                                })
                            }
                            disabled={!activeQG} >
                            Delete
                        </button>
                    </div>
                    { /* Button for going to Common Queries page */ }
                    <div className="commonQueriesContainer">
                        <Link to="/common-queries">
                            <button className="commonQueriesButton">
                                Common Queries
                            </button>
                        </Link>
                    </div>
                </div>

              
                <Routes>
                    { /* Defines route for common queries*/}
                    <Route
                        path="/common-queries"
                        element={
                            <CommonQueries
                                queryList={queryList}
                                commonQueryClick={commonQueryClick}
                            />
                        }
                    />

                    { /* Handles the query groups themselves, so the query group, bubbles, input box, getting user input, etc. */}
                    <Route
                        path="/"
                        element={
                            <div className="rightSide">
                                <h1>{activeQG || "Select a Query Group"}</h1>
                                <div className="bubbles" ref={bubblesRef}>
                                    {activeQG &&
                                        QG[activeQG]?.messages.map((item, index) => (
                                            <div key={index} className={`bubble ${item.isUser ? "userBubble" : "autoBubble" }`} >
                                                <p>{item.query}</p>
                                            </div>
                                        ))}
                                </div>
                                <textarea
                                    className="userInputBox"
                                    placeholder="Enter query here"
                                    value={query}
                                    onChange={(e) => setQuery(e.target.value)}
                                    onKeyDown={newInputEntered}
                                    disabled={!activeQG}
                                />
                            </div>
                        }
                    />
                   
                </Routes>

                { /* Handles the overlay for creating a new query group */}
                {showOverlay && (
                    <div className="overlay">
                        <div className="overlayContent">
                            <h2>New Query Group</h2>
                            <input
                                type="text"
                                placeholder="Enter Query Group Name"
                                value={newQGName}
                                onChange={(e) => setNewQGName(e.target.value)}
                                autoFocus
                            />
                            <button onClick={addNewQG}>Add Query Group</button>
                            <button onClick={() => setShowOverlay(false)}>Cancel</button>
                        </div>
                    </div>
                )}
            </div>
        </Router>
    );
}

export default App;
