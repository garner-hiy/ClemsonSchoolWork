import React from "react";
import { useNavigate } from "react-router-dom";


/*
Creates a container for the common queries,
then adds the header "Most Common Queries"
Converts the queryList object to key-values,
then sorts the list of queries and gets the top 10,
creates list elements for each query within the list,
uses commonQueryClick if the user clicks on the query to go back
to App.jsx and handle that. Has a "Back to Query Groups" button which
uses nav to go back to the Query Groups page.
*/
function CommonQueries({queryList, commonQueryClick}) {
    const nav = useNavigate();
    return (
        <div className="CommonQueries">
            <h1>Most Common Queries</h1>
            <ul className="CommonQueriesList">
                {Object.entries(queryList)
                    .sort((query, value) => value[1] - query[1])
                    .slice(0, 10)
                    .map(([queryText], index) => (
                        <li key={index} onClick={() => commonQueryClick(queryText, nav)} >
                            {queryText}
                        </li>
                    ))}
            </ul>
            <button onClick={() => nav("/")}>Back to Query Groups</button>
        </div>
    );
}

export default CommonQueries;
