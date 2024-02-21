db.createUser({
    user: "aacuser",
    pwd: "3935",
    roles: [
        {
            role: "readWrite",
            db: "AAC"
        }
    ]
});
